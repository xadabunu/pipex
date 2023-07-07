/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:09:03 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/07 23:58:09 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(char **env, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return ((char *)cmd);
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

static void	ft_pipe(t_pipex *pipex)
{
	if (pipe(pipex->pipe) == -1)
	{
		perror("pipe");
		pipex->pipe[WR_END] = -1;
		pipex->pipe[RD_END] = -1;
	}
}

static void	dup_fds(int fd_read, int fd_write, t_pipex *pipex)
{
	int	a;
	int	b;

	a = dup2(fd_read, STDIN_FILENO);
	b = dup2(fd_write, STDOUT_FILENO);
	close(fd_read);
	close(fd_write);
	if (a == -1 || b == -1)
	{
		pipex->exit_code = EXIT_FAILURE;
		ft_leave(pipex);
	}
}

static void	exec_child(t_pipex *pipex, char *cmd, int fd_read, int fd_write)
{
	char	*temp;

	dup_fds(fd_read, fd_write, pipex);
	close(pipex->pipe[RD_END]);
	pipex->args = ft_split(cmd, ' ');
	if (!pipex->args)
		perror("ft_split");
	else
	{
		temp = pipex->args[0];
		pipex->args[0] = get_path(pipex->envp, temp);
		free(temp);
	}
	execve(pipex->args[0], pipex->args, pipex->envp);
	ft_putstr_fd("Command not found: ", STDERR_FILENO);
	ft_putendl_fd(pipex->args[0], STDERR_FILENO);
	pipex->exit_code = COMMAND_NOT_FOUND;
	ft_leave(pipex);
}

void	exec_cmd(t_pipex *pipex, unsigned int n, char *cmd)
{
	int	fd_read;
	int	fd_write;
	int	id;

	fd_read = pipex->pipe[RD_END];
	if (n == pipex->last_cmd_index)
		fd_write = pipex->fd_outfile;
	else
	{
		ft_pipe(pipex);
		fd_write = pipex->pipe[WR_END];
	}
	id = fork();
	if (id == 0)
		exec_child(pipex, cmd, fd_read, fd_write);
	close(fd_read);
	close(fd_write);
	if (id == -1)
		perror("fork");
	if (n == pipex->last_cmd_index)
		pipex->last_id = id;
}
