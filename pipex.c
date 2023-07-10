/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 18:31:55 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/10 23:42:28 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_wait(t_pipex *pipex);

static int	check_args(int argc, char **argv)
{
	const char	*err1 = "Usage: ./pipex file cmd ... cmd file";
	const char	*err2 = "Usage: ./pipex here_doc LIMITER file cmd ... cmd file";
	int			bool;

	bool = (argc > 1 && ft_strncmp(argv[1], "here_doc", 9) == 0);
	if (bool == 1 && argc < 6)
	{
		ft_putendl_fd((char *)err2, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (bool == 0 && argc < 5)
	{
		ft_putendl_fd((char *)err1, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static char	**parse_path(char **envp)
{
	unsigned int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			if (ft_strncmp(envp[i], "PATH=", 5) == 0)
				return (split_path(envp[i] + 5, ':'));
			++i;
		}
	}
	return (NULL);
}

static void	open_files(t_pipex *p)
{
	p->pipe[RD_END] = open(p->infile, O_RDONLY);
	if (p->pipe[RD_END] == -1)
		perror("infile");
	if (p->here_doc)
		p->fd_outfile = open(p->outfile, O_CREAT | O_WRONLY | O_APPEND, 0662);
	else
		p->fd_outfile = open(p->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0662);
	if (p->pipe[WR_END] == -1)
		perror("outfile");
}

static void	create_pipex(t_pipex *p, char **envp, char **argv, int argc)
{
	p->here_doc = ft_strncmp(argv[1], "here_doc", 9) == 0;
	p->envp = parse_path(envp);
	if (p->envp == NULL)
		perror("envp error");
	if (p->here_doc == 1 && here_doc(argv[2], ft_strlen(argv[2]), p) == -1)
	{
		free_struct(p);
		exit (2);
	}
	else
		p->infile = argv[1];
	p->envp_copy = envp;
	p->outfile = argv[argc - 1];
	p->last_cmd_index = argc - 2;
	p->exit_code = 0;
	open_files(p);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		n;

	if (check_args(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	create_pipex(&pipex, envp, argv, argc);
	n = 2 + pipex.here_doc;
	while (n < argc - 1)
	{
		exec_cmd(&pipex, n, argv[n]);
		++n;
	}
	ft_wait(&pipex);
	ft_leave(&pipex);
	return (0);
}
