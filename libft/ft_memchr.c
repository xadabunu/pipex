/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:04:50 by xadabunu          #+#    #+#             */
/*   Updated: 2022/10/03 15:55:37 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	if (!s || n == 0)
		return (NULL);
	str = (unsigned char *)s;
	c = (unsigned char)c;
	while (n > 0)
	{
		if (*str == c)
			return (str);
		--n;
		++str;
	}
	return (NULL);
}
