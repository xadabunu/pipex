/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:08:28 by xadabunu          #+#    #+#             */
/*   Updated: 2022/10/28 11:46:28 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*s_dest;
	char	*s_src;
	size_t	i;

	if (n == 0)
		return (dest);
	if (!dest && !src)
		return (NULL);
	s_dest = (char *)dest;
	s_src = (char *)src;
	i = 0;
	while (i < n)
	{
		s_dest[i] = s_src[i];
		++i;
	}
	return (dest);
}
