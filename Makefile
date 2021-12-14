.PHONY: NAME GCC INCL CFLAGS SRC OBJ all clean fclean re

NAME	= test

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

SRC 	= main.c

OBJ		= $(SRC:.c=.o)

all:	$(SRC) $(NAME)

$(NAME): $(OBJ)
	${CC} ${CFLAGS} -o ${NAME} ${OBJ}

clean:
	rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all