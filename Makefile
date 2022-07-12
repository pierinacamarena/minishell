# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 18:52:14 by pcamaren          #+#    #+#              #
#    Updated: 2022/07/06 18:52:23 by pcamaren         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -g
FLAGS = -Wall -Wextra
HEADER = includes
SRC = src
OBJ = objects
SOURCES =	minishell.c \
			ft_utils.c \
			built_in.c \
			basic_parsing.c \
			cd.c \
			ft_split.c \
			env.c \
			env_for_execute.c

SRCS = $(addprefix $(SRC)/, $(SOURCES))
OBJS = $(addprefix $(OBJ)/, $(SOURCES:.c=.o))

all: $(OBJ) $(NAME)

$(OBJ):
	mkdir -p $(OBJ)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(THREADS) -o $(NAME) $(OBJS) -g -lreadline

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(FLAGS) $(THREADS) -o $@ -c $^ -I$(HEADER)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
