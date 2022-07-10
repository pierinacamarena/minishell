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
CC = gcc
FLAGS = -Wall -Werror -Wextra
HEADER = includes
SRC = src
OBJ = objects
# SOURCES =	main.c \
# 			built_in.c \
# 			cd.c \
# 			execute.c \
# 			ft_utils.c \
# 			gnl.c \
# 			pwd.c \
# 			ft_strcmp.c
SOURCES =	minishell.c \
			gnl.c \
			ft_utils.c \

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
