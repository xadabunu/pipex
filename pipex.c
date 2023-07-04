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

int	check_args(int argc, char **argv, t_pipex *p)
{
	const char	*err1 = "Usage: ./pipex file cmd ... cmd file";
	const char	*err2 = "Usage: ./pipex here_doc LIMITER file cmd ... cmd file";
	
	p->here_doc = argc > 1 && ft_strncmp(argv[1], "here_doc", 9) == 0;
	if (p->here_doc && argc < 6)
	{
		ft_putendl_fd(err2, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!p->here_doc && argc < 5)
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
		free(pipex);
	}
	return (NULL);
}

char **free_path(char **path)
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

t_pipex	*create_pipex(char **envp, char **argv, int argc)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(*pipex));
	if (pipex)
	{
		pipex->envp = parse_path(envp);
		if (pipex->envp == NULL)
			perror("envp error");
		if (pipex->here_doc == 1)
			pipex->infile = ".pipex_hidden_file";
		else
			pipex->infile = argv[1];
		pipex->outfile = argv[argc - 1];
		pipex->fd = malloc((sizeof(pipex->fd)) * (argc - 2 - pipex->here_doc));
		if (!pipex->fd)
		{
			free(pipex->envp);
			free(pipex);
			return (NULL);
		}
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

char	*get_path(char **env, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
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
	char	*temp;
	int		id;
	
	id = fork();
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
		}
		free(temp);
		execve(pipex->args[0], pipex->args, pipex->envp);
	}
}

void	exec_last_cmd(t_pipex	*pipex, char *cmd)
{
	
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		n;

	if (check_args() == EXIT_FAILURE)
		exit(2);
	pipex = create_pipex(envp);
	if (!pipex)
		return (2);
	if (pipex->here_doc)
		here_doc(argv[2], ft_strlen(argv[2]), pipex);
	exec_first_cmd(pipex, argv[1]);
	n = 0;
	while (n++ < argc - 3)
		exec_nth_cmd(pipex, n);
	exec_loop_cmd(pipex, argv);
	exec_last_cmd(pipex, argv[argc - 2]);
	parse_argv(pipex, argv);
	free_struct(pipex);
	return (0);
}
