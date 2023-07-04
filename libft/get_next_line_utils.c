/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 21:42:45 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/02 21:42:45 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		++i;
	if (str[i] == '\n')
		++i;
	return (i);
}

char	*gnl_join(char *s1, char *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*str;

	i = -1;
	len1 = gnlen(s1);
	len2 = gnlen(s2);
	str = ft_calloc(sizeof(char), (len1 + len2 + 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (++i < len1)
		str[i] = s1[i];
	i = -1;
	while (++i < len2)
		str[len1 + i] = s2[i];
	free(s1);
	return (str);
}

char	**init_nl(void)
{
	char	**nl;
	int		i;

	i = 0;
	nl = malloc(OPEN_MAX);
	while (i < OPEN_MAX)
	{
		nl[i] = "\0";
		++i;
	}
	return (nl);
}
