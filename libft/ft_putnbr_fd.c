/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:49:06 by xadabunu          #+#    #+#             */
/*   Updated: 2022/10/03 16:09:22 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_subputnbr_fd(unsigned int n, int fd)
{
	if (n > 9)
		ft_subputnbr_fd(n / 10, fd);
	ft_putchar_fd(48 + n % 10, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	uns_n;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		uns_n = -n;
	}
	else
		uns_n = n;
	ft_subputnbr_fd(uns_n, fd);
}
