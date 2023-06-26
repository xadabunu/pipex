/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:09:05 by xadabunu          #+#    #+#             */
/*   Updated: 2022/10/03 17:13:48 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	c = c % 256;
	while (n > 0)
	{
		str[n - 1] = (unsigned char)c;
		--n;
	}
	return (s);
}
