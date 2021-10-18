/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:53:06 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/18 22:43:38 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_env(char **ap, char *str, char *key)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (ap && ap[i] != NULL)
	{
		if ((ft_strcmp_sep(ap[i], key, '=')) == 0)
		{
			while (*str != '=')
				str++;
			str += 1;
			new = ft_strjoin(ap[i], str);
			free(ap[i]);
			ap[i] = new;
			break ;
		}
		i++;
	}
}

char	**append_add_env(char **ap, char *str, char *key, int l)
{
	int		i;
	char	**new;

	i = 1;
	while (ap && ap[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (ap && ap[i] != NULL)
	{
		new[i] = ap[i];
		i++;
	}
	str += l;
	new[i] = ft_strjoin(key, str);
	new[i + 1] = NULL;
	free(ap);
	return (new);
}

void	check_append_env(t_shell *shell, char *str, int l)
{
	char	*key;

	key = ft_strdup(str);
	key[l] = 0;
	if (search_env(shell->env, key) == NULL)
	{
		if (search_env(shell->exp, key) != NULL)
			shell->exp = delete_env(shell->exp, key);
		key[l] = '=';
		key[l + 1] = 0;
		shell->env = append_add_env(shell->env, str, key, l + 2);
	}
	else
		append_env(shell->env, str, key);
	free(key);
}
