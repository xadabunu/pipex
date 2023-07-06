/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 18:31:55 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/06 02:27:18 by xadabunu         ###   ########.fr       */
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
	if (pipex->envp)
		free(pipex->envp);
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

t_pipex	*create_pipex(t_pipex *p, char **envp, char **argv, int argc)
{
	p->here_doc = ft_strncmp(argv[1], "here_doc", 9) == 0;
	p->envp = parse_path(envp);
	if (p->envp == NULL)
		perror("envp error");
	if (p->here_doc == 1 && here_doc(argv[2], ft_strlen(argv[2]), p) == -1)
	{
		free_struct(p);
		exit (2);
	}
	else
		p->infile = argv[1];
	p->outfile = argv[argc - 1];
	p->last_cmd = argc - 2;
	open_files(p);
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

void	dup_fds(int fd_read, int fd_write, t_pipex *pipex)
{
	int	a;
	int	b;

	a = dup2(fd_read, STDIN_FILENO);
	b = dup2(fd_write, STDOUT_FILENO);
	close(fd_read);
	close(fd_write);
	if (a == -1 || b == -1)
		ft_leave(pipex, EXIT_FAILURE);
}

void	ft_pipe(t_pipex *pipex)
{
	if (pipe(pipex->pipe) == -1)
	{
		perror("pipe");
		pipex->pipe[0] = -1;
		pipex->pipe[1] = -1;
	}
}

void	exec_cmd(t_pipex *pipex,unsigned int n , int cmd)
{
	int	fd_read;
	int	fd_write;
	int	id;

	if (cmd == pipex->last_cmd)
		fd_write = pipex->fd_outfile;
	else
	{
		ft_pipe(pipex);
		fd_write = pipex->pipe[1];
	}
	id = fork();
	if (id == 0)
		exec_child(pipex, pipex->args);
	close(fd_read);
	close(fd_write);
	if (id == -1)
		perror("fork");
	if (/*last cmd*/)
	{
		/*save id => if last cmd failed ?*/
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		n;

	if (check_args(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	create_pipex(pipex, envp, argv, argc);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		here_doc(argv[2], ft_strlen(argv[2]), pipex);
	n = 1;
	while (n++ < argc - 3)
		exec_nth_cmd(pipex, n);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	parse_argv(pipex, argv);
	free_struct(pipex);
	return (0);
}
