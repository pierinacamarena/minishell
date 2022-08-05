# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: .oamaren <.oamaren@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 18:52:14 by .oamaren          #+#    #+#              #
#    Updated: 2022/08/05 13:57:30 by rbourdil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


OBJS	=	./src/minishell.o\
			./src/signal.o\
			./src/env/env_for_execute.o\
			./src/env/env_setup.o\
			./src/env/export_sort.o\
			./src/env/list_utils.o\
			./src/utils/ft_split.o\
			./src/utils/ft_utils.o\
			./src/utils/error.o\
			./src/exec/ft_path.o\
			./src/exec/execute_list.o\
			./src/builtin_list/echo.o\
			./src/builtin_list/builtins_list.o\
			./src/builtin_list/cd_list.o\
			./src/builtin_list/export_list_builtin.o\
			./src/builtin_list/unset_list.o\
			./parse/buffer.o\
			./parse/buffer2.o\
			./parse/expand.o\
			./parse/lexer.o\
			./parse/list.o\
			./parse/parser.o\
			./parse/scanner.o\
			./parse/semantics.o\
			./parse/string_ops.o\
			./parse/utils.o

NAME	=	minishell

CC		=	cc	

CFLAGS	=	-Wall -Werror -Wextra

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${OBJS} -lreadline -o ${NAME}

${OBJS}:	%.o:%.c
			${CC} ${CFLAGS} -Iincludes -c $< -o $@

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re	:		fclean all

.PHONY	:	all fclean clean re
