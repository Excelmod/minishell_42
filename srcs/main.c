/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:35:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/28 22:08:36 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *type_str[7] = {"ERROR", "TEXT", "TRUNC", "APPEND", "HEREDOC", "INPUT", "PIPE"};

char	**new_env(char **ap, char *str)
{
	int i;
	char **new;

	i = 0;
	while (ap[i] != NULL)
		i++;
	if (str)
		i++;
	new = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (ap[i] != NULL)
	{
		new[i] = ft_strdup(ap[i]);
		i++;
	}
	if (str)
		new[i++] = ft_strdup(str);
	new[i] = NULL;
	return (new);
}

void	initialization_shell(t_shell *shell, char **ap)
{
	shell->env = new_env(ap, NULL);
	shell->tokens = NULL;
	shell->path = ft_split(search_env(shell->env, "PATH") + 5, ':');
	if (!(shell->path))
	{
		perror("shell");
		exit(0);
	}
}

void	loop(t_shell *shell)
{
	char 	*line;
	int		error;
	t_token *lst;

	line = NULL;
	handle_prompt();
	while(get_next_line(0, &line))
	{
		error = tokenizer(shell, line);
		lst = shell->tokens;
		while(lst)
		{
			printf("le type est %s et la ligne est :%s\n", type_str[(int)(lst->type)], lst->line);
			lst = lst->next;
		}
		error = check_syntax_error(shell, error);
		if(!error)
			parsing(shell);
		ft_tokenclear(&(shell->tokens));
		free(line);
		line = NULL;
		handle_prompt();
	}
}

int	main(int ac, char **av, char **ap)
{
	t_shell	*sh;

	sh = NULL;
	ac = 0;
	av = 0;
	sh = malloc(sizeof(t_shell));
	if (sh == NULL)
	{
		perror("shell");
		exit(0);
	}
	initialization_shell(sh, ap);
	loop(sh);
	exit_free(sh);
	return (0);
}
