/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:33:30 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/27 20:53:40 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

enum types 
{
	ERROR,
	TEXT,
	TRUNC,
	APPEND,
	HEREDOC,
	INPUT,
	PIPE,
};

typedef	struct	s_token t_token;

typedef struct s_shell
{
	char	**av;
	char	**env;
	char	**path;
	char	*cmd;
	t_token	*tokens;
}	t_shell;

typedef	struct	s_token
{
	enum types	type;
	char		*line;
	t_token		*next;
}	t_token;

int			check_path(t_shell *shell, char *path, char *cmd);
void		search_cmd(t_shell *shell, char *cmd);
void		exit_message_error(t_shell *shell, char *msg);
void		ft_tokenclear(t_token **lst);
char		**ft_freetabs(char **t);
char		*search_env(char **env, char *search);
char 		*cur_dir_name(void);
void    	handle_prompt(void);
void    	tokenizer(t_shell *shell, char *line);
void		exit_free(t_shell *shell);
int			get_next_line(int fd, char** line);
t_token		*ft_tokennew(enum types type, char *line);
void		ft_token_add_back(t_token **atoken, t_token *new);
t_token		*ft_tokenlast(t_token *token);
char		*env_value(char **env, char *search);
#endif
