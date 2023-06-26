/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:08:44 by xadabunu          #+#    #+#             */
/*   Updated: 2022/10/28 12:39:54 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s_dest;
	char	*s_src;

	if (!dest || !src)
		return (NULL);
	if (n == 0)
		return ((void *)dest);
	s_src = (char *)src;
	s_dest = (char *)dest;
	if (src > dest)
	{
		while (n-- > 0)
			*s_dest++ = *s_src++;
	}
	else
	{
		while (n-- > 0)
			s_dest[n] = s_src[n];
	}
	return (dest);
}
