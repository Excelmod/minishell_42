/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:33:30 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/20 05:26:40 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

enum e_types
{
	ERROR,
	TEXT,
	TRUNC,
	APPEND,
	HEREDOC,
	INPUT,
	PIPE,
};

typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;

typedef struct s_context
{
	int	fd_in;
	int	fd_out;
	int	fd_close;
}	t_context;

typedef struct s_token
{
	enum e_types	type;
	char			*line;
	int				fd;
	t_token			*next;
}	t_token;

typedef struct s_cmd
{
	char	**cmds;
	int		fd_in;
	int		fd_out;
	char	*msg_error;
	t_cmd	*next;
	t_cmd	*prev;
}	t_cmd;	

typedef struct s_shell
{
	char	**env;
	char	**exp;
	char	**path;
	int		stdin;
	int		stdout;
	int		exit_status;
	char	*pwd;
	char	*str;
	int		*pipes;
	int		*pid;
	int		nb_cmds;
	t_token	*tokens;
	t_cmd	*cmd;
}	t_shell;

//execution
void		execution(t_shell *shell);
int			check_path(char *path, char	*cmd, char **path_cmd);
char		*path_join(char *s1, char *s2);
int			search_cmd(t_shell *shell, char *cmd, char **path_cmd);
void		exec_command_pipe(t_shell *shell, t_cmd *cmd, int nb);
void		close_pipes(t_shell *shell);
void		exec_multiple_cmd(t_shell *shell, t_cmd *cmd);
//initialization
void		initialization_shell(t_shell *shell, char **ap);
// utils
int			compare(char *in, char *out);
int			get_next_line(int fd, char **line);
// token utils
t_token		*ft_tokennew(enum e_types type, char *line);
void		ft_token_add_back(t_token **atoken, t_token *new);
t_token		*ft_tokenlast(t_token *token);
// tokenizer
int			tokenizer(t_shell *shell, char *line);
int			tokenizer_text(t_shell *shell, int *ind, char *str);
char		*ft_strjoin_part(char *s1, char *spart, int l);
// expansion env
char		*expand_exit_status(t_shell *shell, int *ind, char *l);
char		*expand_var(t_shell *shell, int *ind, char *str, char *l);
char		*expand_var_quote(t_shell *shell, int *ind, char *str, char *l);
// parsing
char		*parsing_tokenizer(t_shell *shell, char *line);
int			check_syntax_error(t_shell *shell, int error);
void		parsing(t_shell *shell);
int			parsing_io_files(t_cmd *cmd, t_token *token);
// heredoc handling
void		handle_prompt_heredoc(void);
void		handle_error_heredoc(t_shell *shell, int count);
// exit , error and free
int			exit_shell(t_shell *shell, char **av);
int			exit_pipe(t_shell *shell, char **av);
char		**ft_freetabs(char **t);
void		free_cmd(t_cmd *cmd);
void		ft_tokenclear(t_token **lst);
void		exit_free(t_shell *shell, int status);
void		message_error(char *msg);
// echo
int			builtin_echo(char **args);
// env
int			builtin_env(t_shell *shell);
char		*env_value(char **env, char *search);
char		*search_env(char **env, char *search);
// export
int			builtin_export(t_shell *shell, char **args);
void		print_export(t_shell *shell);
void		check_append_env(t_shell *shell, char *str, int l);
int			ft_strcmp_sep(char *s1, char *s2, char sep);
// unset
int			builtin_unset(t_shell *shell, char **args);
char		**delete_env(char **ap, char *str);
// cd
int			builtin_cd(t_shell *shell, char **arg);
void		change_pwd(t_shell *shell, char *path);
char		*cur_dir_name(void);
//pwd
int			builtin_pwd(t_shell *shell);
// signal
void		signal_input(void);
void		signal_process(void);
void		signal_ignore(void);
#endif
