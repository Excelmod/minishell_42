/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:35:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/05 19:12:34 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_env(char **ap)
{
	int i;
	char **new;

	i = 0;
	while (ap && ap[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (ap && ap[i] != NULL)
	{
		new[i] = ft_strdup(ap[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	initialization_shell(t_shell *shell, char **ap)
{
	shell->env = new_env(ap);
	shell->exp = NULL;
	shell->tokens = NULL;
	shell->path = ft_split(search_env(shell->env, "PATH") + 5, ':');
	shell->stdin = dup(0);
	shell->stdout = dup(1);
	shell->exit_status = 0;
	if (!(shell->path))
	{
		perror("shell");
		exit(0);
	}
}

void	loop(t_shell *shell)
{
	char 	*line;

	line = NULL;
	while((line = readline("Minishell :")) != NULL)
	{
		line = parsing_tokenizer(shell, line); // fonction regroupant toute les fonctions parsing et tokenization,  qui free line et retourne NULL,
		starting_execution(shell);
	}
}

int	main(int ac, char **av, char **ap)
{
	t_shell	*sh;

	sh = NULL;
	if (ac && av)
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
