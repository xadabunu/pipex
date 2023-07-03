/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 21:24:33 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/02 21:24:33 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	update_nl(char *nl)
{
	size_t	reader;
	size_t	writer;

	reader = 0;
	while (nl[reader] && nl[reader] != '\n')
		++reader;
	if (nl[reader])
		++reader;
	writer = 0;
	while (nl[reader])
		nl[writer++] = nl[reader++];
	while (nl[writer])
		nl[writer++] = '\0';
}

static char	*gnl_copy(char *src, long fd, char *buffer)
{
	char	*dest;
	size_t	len;
	long	ret;

	ret = 1;
	len = gnlen(src);
	dest = ft_calloc(sizeof(char), len + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, len);
	update_nl(src);
	while (dest[len - 1] != '\n' && ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret > 0)
		{
			ft_strlcpy(src, buffer, ret);
			dest = gnl_join(dest, src);
			update_nl(src);
			len = gnlen(dest);
		}
		else if (ret < 0)
			return (gnfree(dest));
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	nl[OPEN_MAX][BUFFER_SIZE + 1];
	char		buffer[BUFFER_SIZE];
	long		ret;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	if (nl[fd][0] == '\0')
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 1)
			return (NULL);
		ft_strlcpy(nl[fd], buffer, ret);
	}
	return (gnl_copy(nl[fd], fd, buffer));
}
