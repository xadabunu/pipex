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
# include <sys/wait.h>
# include "libft/libft.h"

# define WR_END 1
# define RD_END 0
# define COMMAND_NOT_FOUND 127

typedef struct s_pipex
{
	char			**envp;
	char			**envp_copy;
	char			**args;
	char			*path;
	unsigned int	last_cmd_index;
	int				pipe[2];
	int				here_doc;
	char			*infile;
	int				fd_infile;
	char			*outfile;
	int				fd_outfile;
	int				last_id;
	int				exit_code;
}				t_pipex;

char	**split_path(const char *s, char c);
t_pipex	*free_struct(t_pipex *pipex);
char	**free_path(char **path);
void	exec_cmd(t_pipex *pipex, unsigned int n, char *cmd);
int		here_doc(char *limiter, int len, t_pipex *pipex);
void	ft_leave(t_pipex *pipex);

#endif
