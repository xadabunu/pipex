/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 21:45:03 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/02 21:45:03 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef OPEN_MAX
#  define OPEN_MAX 50
# endif
# define BUFFER_SIZE 50

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
void	*ft_calloc(size_t nmemb, size_t size);

char	**init_nl(void);
char	*gnl_join(char *s1, char *s2);
size_t	gnlen(const char *str);
void	gncopy(char *dest, char *src, int len);

#endif