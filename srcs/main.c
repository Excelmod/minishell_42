/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:35:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/03 18:27:03 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	line = NULL;
	handle_prompt();
	while(get_next_line(0, &line))
	{
		line = parsing_tokenizer(shell, line); // fonction regroupant toute les fonctions parsing et tokenization,  qui free line et retourne NULL, 
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
