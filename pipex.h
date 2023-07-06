/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:17:56 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/04 16:17:59 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_pipex
{
	const char	**envp;
	char		**args;
	char		**path;
	int			last_cmd;
	int			pipe[2];
	int			here_doc;
	char		*infile;
	int			fd_infile;
	char		*outfile;
	int			fd_outfile;
}				t_pipex;

char	**split_path(const char *s, char c);

#endif
