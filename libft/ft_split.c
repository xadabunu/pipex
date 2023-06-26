/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:09:28 by xadabunu          #+#    #+#             */
/*   Updated: 2022/10/28 16:19:35 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_count(const char *str, char c)
{
	int	i;
	int	ctr;

	i = 0;
	ctr = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			++ctr;
			while (str[i] && str[i] != c)
				++i;
			--i;
		}
		++i;
	}
	return (ctr);
}

static char	**ft_assign(const char *str, char **tab, int size, char c)
{
	int	i;
	int	n;
	int	j;

	n = 0;
	i = 0;
	while (n < size)
	{
		if (str[i] != c)
		{
			j = 0;
			while (str[i] && str[i] != c)
				tab[n][j++] = str[i++];
			tab[n][j] = '\0';
			++n;
		}
		++i;
	}
	tab[n] = 0;
	return (tab);
}

static int	ft_splitlen(const char *str, char c, int *pos)
{
	int	j;

	while (str[*pos] && str[*pos] == c)
		++*pos;
	j = *pos;
	while (str[*pos] && str[*pos] != c)
		++*pos;
	return (*pos - j);
}

static char	**ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	int		size;
	char	**tab;
	int		i;
	int		len;
	int		pos;

	if (!s)
		return (0);
	size = str_count(s, c);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (0);
	i = 0;
	pos = 0;
	while (i < size)
	{
		len = ft_splitlen(s, c, &pos);
		tab[i] = malloc(sizeof(char) * (1 + len));
		if (!tab[i])
			return (ft_free(tab));
		++i;
	}
	return (ft_assign(s, tab, size, c));
}
