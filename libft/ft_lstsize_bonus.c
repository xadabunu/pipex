/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:11:23 by xadabunu          #+#    #+#             */
/*   Updated: 2022/10/19 14:25:52 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	ctr;

	if (!lst)
		return (0);
	ctr = 1;
	while (lst->next)
	{
		++ctr;
		lst = lst->next;
	}
	return (ctr);
}
