# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 18:31:48 by xadabunu          #+#    #+#              #
#    Updated: 2023/07/06 02:28:27 by xadabunu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

SRCS	=	pipex.c

OBJS	=	${SRCS:.c=.o}

CFLAGS	=	-Wall -Wextra -Werror

LDFLAGS	=	-Llibft

LDLIBS	=	-lft

RM		=	rm -rf

LIB_DIR	=	libft

LIBFT	=	${LIB_DIR}/libft.a

all		:	${NAME}

${NAME}	:	${OBJS} ${LIBFT}
			${CC} ${LDFLAGS} ${OBJS} ${LDLIBS} -o ${NAME}

${LIBFT}:
			${MAKE} -C ${LIB_DIR}

bonus	:	${NAME}

clean	:
			${MAKE} clean -C ${LIB_DIR}
			${RM} ${OBJS}

fclean	:	clean
			${RM} ${LIBFT}
			${RM} ${NAME}

re		:	fclean all

.PHONY	:	all clean fclean re bonus
