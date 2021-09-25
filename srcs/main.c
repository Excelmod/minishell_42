/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:35:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/24 22:14:08 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_freetabs(char **t)
{
	int	i;

	i = 0;
	while (t[i] != NULL)
	{
		free(t[i]);
		t[i] = NULL;
		i++;
	}
	free(t);
	t = NULL;
	return (NULL);
}

char	**new_env(t_shell *sh, char **ap, char *str)
{
	int i;
	char **new;

	i = 0;
	while (ap[i] != NULL)
		i++;
	if (str)
		i++;
	malloc(sizeof(char *) * i + 1);
	i = 0;
	while (ap[i] != NULL)
		new[i] = f_strdup(ap[i++]);
	if (str)
		new[i++] = f_strdup(str);
	new[i] = NULL;
	return (new);
}

void	initialization_shell(t_shell *shell, char **av, char **ap)
{
	shell->ap = new_env(shell, ap, NULL);
	shell->path = ft_split(search_env(shell->ap, "PATH") + 5, ':');
	if (!(shell->path))
	{
		perror("shell");
		exit(0);
	}
}

int	main(int ac, char **av, char **ap)
{
	t_shell	*sh;

	sh = NULL;
	sh = malloc(sizeof(t_shell));
	if (shell == NULL)
	{
		perror("shell");
		exit(0);
	}
	initialization_shell(sh, av, ap);
	exit_free(shell);
	return (0);
}
