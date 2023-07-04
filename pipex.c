/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 18:31:55 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/04 01:26:12 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_args(int argc, char **argv)
{
	const char	*err1 = "Usage: ./pipex file cmd ... cmd file";
	const char	*err2 = "Usage: ./pipex here_doc LIMITER file cmd ... cmd file";
	int			bool;

	bool = (argc > 1 && ft_strncmp(argv[1], "here_doc", 9) == 0);
	if (bool == 1 && argc < 6)
	{
		ft_putendl_fd(err2, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (bool == 0 && argc < 5)
	{
		ft_putendl_fd(err1, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_pipex	*free_struct(t_pipex *pipex)
{
	if (pipex)
	{
		if (pipex->envp)
			free(pipex->envp);
		free(pipex);
	}
	return (NULL);
}

char	**free_path(char **path)
{
	int	i;

	i = 0;
	if (path)
	{
		while (path[i])
			free(path[i]);
		++i;
	}
	return (NULL);
}

static char	**parse_path(char **envp)
{
	unsigned int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			if (ft_strncmp(envp[i], "PATH=", 5) == 0)
				return (split_path(envp[i] + 5, ':'));
			++i;
		}
	}
	return (NULL);
}

void	open_files(t_pipex *p)
{
	p->fd[0] = open(p->infile, O_RDONLY);
	p->fd[1] = open(p->outfile, O_WRONLY | O_TRUNC);
}

t_pipex	*create_pipex(char **envp, char **argv, int argc)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(*pipex));
	if (pipex)
	{
		pipex->here_doc = ft_strncmp(argv[1], "here_doc", 9) == 0;
		pipex->envp = parse_path(envp);
		if (pipex->envp == NULL)
			perror("envp error");
		if (pipex->here_doc == 1 && \
			here_doc(argv[2], ft_strlen(argv[2]), pipex) == -1)
		{
			free_struct(pipex);
			exit (2);
		}
		else
			pipex->infile = argv[1];
		pipex->outfile = argv[argc - 1];
		open_files(pipex);
	}
	return (pipex);
}

void	parse_argv(t_pipex *pipex, char **argv)
{
	pipex->args = ft_split(argv[1], ' ');
	if (!pipex->args)
	{
		perror("split error");
		return ;
	}
}

char	*get_path(char **env, const char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (NULL);
	}
	while (env[i] != NULL)
	{
		temp = ft_strjoin(env[i], cmd);
		if (!temp)
		{
			perror("ft_strjoin");
			return (NULL);
		}
		if (access(temp, X_OK) == 0)
			return (temp);
		free(temp);
		++i;
	}
	return (NULL);
}

void	exec_first_cmd(t_pipex *pipex, char *cmd)
{
	const int	id = fork();
	char		*temp;

	if (id == -1)
	{
		perror("fork");
		return ;
	}
	if (id == 0)
	{
		pipex->args = ft_split(cmd, " ");
		if (!pipex->args)
			perror("ft_split");
		else
		{
			temp = pipex->args[0];
			pipex->args[0] = get_path(pipex->envp, cmd);
			free(temp);
		}
		execve(pipex->args[0], pipex->args, pipex->envp);
	}
}

void	exec_last_cmd(t_pipex	*pipex, char *cmd)
{
	const int	id = fork();
	char		*temp;
}

void	exec_nth_cmd(t_pipex *pipex, unsigned int n)
{
	if (pipe(pipex->fd) == -1)
	{
		perror("pipe");
	}
	if (n == 1)
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		n;

	if (check_args(argc, argv) == EXIT_FAILURE)
		exit(2);
	pipex = create_pipex(envp, argv, argc);
	if (!pipex)
		return (2);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		here_doc(argv[2], ft_strlen(argv[2]), pipex);
	exec_first_cmd(pipex, argv[1]);
	n = 1;
	while (n++ < argc - 3)
		exec_nth_cmd(pipex, n);
	exec_last_cmd(pipex, argv[argc - 2]);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	parse_argv(pipex, argv);
	free_struct(pipex);
	return (0);
}
