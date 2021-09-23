

# Name of the final executable
NAME = minishell

# Create a list of *.c sources in DIRS
SOURCES = srcs/main.c srcs/search_cmd.c srcs/prompt.c srcs/check_path.c

# Define objects for all sources
OBJS = $(SOURCES:.c=.o)

# Define headers files
CFLAGS = -Wall -Werror -Wextra
HEADERS = -I include -I libft

# Name the compiler
CC = gcc


all: libft.a $(NAME)

%.o : %.c
	gcc -c $(CFLAGS) $(HEADERS) $< -o $@

libft.a :
	cd libft && $(MAKE) && mv libft.a ../

$(NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) libft.a

# Remove all objects, dependencies and executable files generated during the build
clean:
	rm -f $(OBJS)
	cd libft/ && make clean
	@echo Objects files delete done !

fclean: clean
	rm -f $(NAME) libft.a
	@echo Cleaning done !

re: fclean all

.PHONY: all clean  fclean re
