/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:06:36 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/07 22:12:03 by xadabunu         ###   ########.fr       */
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

void	ft_wait(t_pipex *pipex)
{
	int	status;
	
	if (pipex->last_id != -1)
	{
		waitpid(pipex->last_id, &status, 0);
		if (WIFEXITED(status))
			pipex->exit_code = WIFEXITED(status);
		else
			pipex->exit_code = EXIT_FAILURE;
	}
	else
		pipex->exit_code = EXIT_FAILURE;
	while (wait(NULL) != -1 || errno != ECHILD)
		;
}
