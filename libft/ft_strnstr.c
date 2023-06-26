/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:04:22 by xadabunu          #+#    #+#             */
/*   Updated: 2022/09/23 12:04:24 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	if (!to_find)
		return ((char *)str);
	i = 0;
	if (to_find[0] == 0)
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == to_find[j] && i + j < len)
		{
			if (to_find[j] == '\0')
				return ((char *)(str + i));
			++j;
		}
		if (to_find[j] == 0)
			return ((char *)(str + i));
		++i;
	}
	return (NULL);
}
