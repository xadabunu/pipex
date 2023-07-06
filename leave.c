/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:06:36 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/06 18:32:14 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_leave(t_pipex *pipex)
{
	if (pipex->here_doc)
		unlink(pipex->infile);
	free_struct(pipex);
	exit(pipex->exit_code);
}
