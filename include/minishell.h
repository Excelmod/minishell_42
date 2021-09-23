/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:33:30 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/23 22:45:41 by ljulien          ###   ########.fr       */
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
# include "libft.h"

enum types 
{
	CMD,
	TRUNC,
	APPEND,
	HEREDOC,
	INPUT,
	PIPE,
}

typedef struct s_shell
{
	char	**av;
	char	**ap;
	char	**path;
	char	*cmd;
}	t_shell;

typedef	struct	s_token
{
	int  types;
	char *;
}	t_token;

int			check_path(t_pipex *pipex, char *path, char *cmd);
void		exec_cmd(t_pipex *pipex, char **arg);
char		**ft_freetabs(char **t);
char		*search_env(char **env, char *search);
char 		*cur_dir_name(void);
void    	handle_prompt(void);

#endif
