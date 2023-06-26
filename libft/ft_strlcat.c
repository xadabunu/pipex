/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:03:04 by xadabunu          #+#    #+#             */
/*   Updated: 2022/10/18 15:09:50 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	destlen;
	size_t	i;
	size_t	j;

	if (!dest || !src)
		return (0);
	srclen = ft_strlen(src);
	destlen = ft_strlen(dest);
	if (size == 0 || destlen >= size)
		return (srclen + size);
	i = 0;
	j = destlen;
	while (src[i] && i < size - destlen - 1)
	{
			dest[j] = src[i];
			++i;
			++j;
	}
	dest[j] = 0;
	return (destlen + srclen);
}
