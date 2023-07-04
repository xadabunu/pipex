/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:16:20 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/01 17:16:20 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(const char *limiter, int len, t_pipex *pipex)
{
	const int	fd = open(pipex->infile, O_CREAT | O_EXCL | O_WRONLY);
	char		*line;

	if (fd == -1)
		return (-1);
	limiter[len] = '\n';
	ft_putstr_fd("> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, limiter, ft_strlen(limiter) + 1) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	if (line)
		free(line);
	close(fd);
	return (1);
}