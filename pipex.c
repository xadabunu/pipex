/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 18:31:55 by xadabunu          #+#    #+#             */
/*   Updated: 2023/06/27 00:38:29 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*free_struct(t_pipex *pipex)
{
	if (pipex)
	{
		if (pipex->first_cmd)
			free(pipex->first_cmd);
		if (pipex->second_cmd)
			free(pipex->second_cmd);
		free(pipex);
	}
	return (NULL);
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
				return (ft_split(envp[i] + 5, ':'));
			++i;
		}
	}
	return (NULL);
}

t_pipex *create_pipex(char **envp)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(*pipex));
	if (pipex)
	{
		pipex->first_cmd = malloc(sizeof(*(pipex->first_cmd)));
		pipex->second_cmd = malloc(sizeof(*(pipex->second_cmd)));
		if (!pipex->first_cmd || !pipex->second_cmd)
			return (free_struct(pipex));
		pipex->path = parse_path(envp);
	}
	return (pipex);
}

void	parse_argv(t_pipex *pipex, int argc, char **argv)
{
	(void)pipex;
	(void)argc;
	(void)argv;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
	{
		perror("Usage: ./pipex infile cmd1 cmd2 outfile");
		exit(2);
	}
	pipex = create_pipex(envp);
	if (!pipex)
		return (2);
	parse_argv(pipex, argc, argv);
	int i = 0;
	for (; pipex->path[i] ; ++i)
	{
		printf("%s\n", pipex->path[i]);
	}
	free_struct(pipex);
	return (0);
}
