SRCS	   = $(wildcard *.c)
OBJS	   = ${SRCS:.c=.o}
NAME	   = libft.a
CFLAGS	   = -Wall -Wextra -Werror
RM	   = rm -f
CC	   = gcc
BONUS = .bonus
all:		${NAME}

$(NAME):	${OBJS}
				ar crs ${NAME} ${OBJS}

clean:
				${RM} ${OBJS}

fclean:		clean
				${RM} ${NAME}

re:			fclean	all

.PHONY: clean re fclean all
