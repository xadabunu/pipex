/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:16:20 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/16 18:37:11 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_next_line(int fd);

int	here_doc(char *limiter, int len, t_pipex *pipex)
{
	const char	*file = ".pipex_hidden_file";
	const int	fd = open(file, O_CREAT | O_EXCL | O_WRONLY, 0700);
	char		*line;

	if (fd == -1)
		return (-1);
	limiter[len] = '\n';
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, limiter, len) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(fd);
	pipex->infile = (char *)file;
	return (1);
}
