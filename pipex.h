/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:45:21 by xadabunu          #+#    #+#             */
/*   Updated: 2023/06/25 11:45:21 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"
# include <errno.h>

typedef struct	s_cmd
{
	char	*name;
	char	**args;
}				t_cmd;

typedef struct	s_pipex
{
	unsigned int	argc;
	const char		**argv;
	const char		**envp;
	t_cmd			*first_cmd;
	t_cmd			*second_cmd;
	char			**path;
}				t_pipex;

#endif