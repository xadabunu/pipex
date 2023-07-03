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

int	here_doc(const char *limiter)
{
	const char	*file = ".pipex_hidden_file";
	int			fd;
	char		*line;

	fd = open(file, O_CREAT | O_EXCL | O_WRONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) != '\n')
		{
			ft_putstr_fd(line, fd);
			free(line);
			line = get_next_line(fd);
		}
		else
			free(line);
	}
	close(fd);
}