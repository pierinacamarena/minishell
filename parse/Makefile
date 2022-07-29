NAME = parser

OBJS = main_test.o scanner.o parser.o expand.o list.o str_ops.o buffer.o utils.o lexer.o

HEADS = common_defs.h include.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

$(OBJS):	%.o:%.c $(HEADS)
			$(CC) $(CFLAGS) -c $< -o $@

clean:		
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
