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

typedef struct	s_pipex
{
	const char		**envp;
	char			**args;
	char			**path;
	int				*fd[2];
	int				here_doc;
	char			*infile;
	char			*outfile;
}				t_pipex;

char	**split_path(const char *s, char c);

#endif