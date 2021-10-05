

# Name of the final executable
NAME = minishell

# Create a list of .c sources in DIRS
SOURCES =  	srcs/check_path.c		srcs/get_next_line.c 		srcs/parsing.c 				srcs/export.c	\
			srcs/search_cmd.c	 	srcs/exit_free.c	 		srcs/main.c	 				srcs/prompt.c 	\
			srcs/tokenizer.c	 	srcs/token_utils.c	 		srcs/check_syntax_error.c 					\
			srcs/env.c 	  			srcs/parsing_tokenizer.c	srcs/echo.c	  								\
			srcs/print_export.c		srcs/unset.c															\
			srcs/display_struct.c	srcs/start_exec.c			srcs/compare.c								\
# Define objects for all sources
OBJS = $(SOURCES:.c=.o)
RL = -lreadline

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
	$(CC) -g3 -fsanitize=address  $(RL) -o $@ $(OBJS) libft.a

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
