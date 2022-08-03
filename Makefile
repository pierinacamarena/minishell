# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 18:52:14 by pcamaren          #+#    #+#              #
#    Updated: 2022/08/03 17:53:00 by pcamaren         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS	=	./src/minishell.c\
			./src/signal.c\
			./src/env/env_for_execute.c\
			./src/env/env_setup.c\
			./src/env/export_sort.c\
			./src/env/list_utils.c\
			./src/utils/ft_split.c\
			./src/utils/ft_utils.c\
			./src/exec/ft_path.c\
			./src/exec/execute_list.c\
			./src/builtin_list/echo.c\
			./src/builtin_list/builtins_list.c\
			./src/builtin_list/cd_list.c\
			./src/builtin_list/export_list_builtin.c\
			./src/builtin_list/unset_list.c\
			./parse/buffer.c\
			./parse/buffer2.c\
			./parse/expand.c\
			./parse/lexer.c\
			./parse/list.c\
			./parse/parser.c\
			./parse/scanner.c\
			./parse/semantics.c\
			./parse/string_ops.c\
			./parse/utils.c

OBJS	=	${SRCS:.c=.o}

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra -g3

NAME	=	minishell

.c		:	.o
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}	:	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -lreadline -o ${NAME}

all		:	${NAME}

clean	:
			rm -rf ${OBJS}

fclean	:	clean
			rm -rf ${NAME}
			$(MAKE) -C . clean

re	:	fclean all

.PHONY	:	all clean fclean re