# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 18:52:14 by .oamaren          #+#    #+#              #
#    Updated: 2022/08/07 14:53:14 by pcamaren         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


OBJS	=	./src/minishell.o\
			./src/signal.o\
			./src/env/env_for_execute.o\
			./src/env/env_setup.o\
			./src/env/env_utils.o\
			./src/env/export_sort.o\
			./src/env/sort_utils.o\
			./src/env/list_utils.o\
			./src/env/list_utils_utils.o\
			./src/utils/ft_split.o\
			./src/utils/ft_utils.o\
			./src/utils/utils_one.o\
			./src/utils/utils_two.o\
			./src/utils/utils_three.o\
			./src/utils/utils_four.o\
			./src/utils/error.o\
			./src/exec/ft_path.o\
			./src/exec/execute_list.o\
			./src/exec/pipex.o\
			./src/exec/pipex_utils.o\
			./src/builtin_list/echo.o\
			./src/builtin_list/builtins_list.o\
			./src/builtin_list/cd_list.o\
			./src/builtin_list/export_list_builtin.o\
			./src/builtin_list/unset_list.o\
			./src/builtin_list/unset_utils.o\
			./src/builtin_list/built_in_utils.o\
			./src/parse/buffer.o\
			./src/parse/buffer2.o\
			./src/parse/expand.o\
			./src/parse/expand2.o\
			./src/parse/lexer.o\
			./src/parse/list.o\
			./src/parse/parser.o\
			./src/parse/scanner.o\
			./src/parse/semantics.o\
			./src/parse/semantics2.o\
			./src/parse/string_ops.o\
			./src/parse/string_ops2.o\
			./src/parse/utils.o

NAME	=	minishell

CC		=	cc -g	

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
