NAME = parser

OBJS = main_test.o scanner.o parser.o expand.o list.o string_ops.o string_ops2.o buffer.o buffer2.o utils.o lexer.o semantics.o

HEADS = common_defs.h buffer.h expand.h lexer.h list.h parser.h scanner.h semantics.h string_ops.h utils.h

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
