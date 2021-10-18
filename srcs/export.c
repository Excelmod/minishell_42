/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 19:17:39 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/18 22:42:26 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_export(char *str, int *env)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (i == 0 && (ft_isalpha(str[i]) == 0 && str[i] != '_'))
			return (0);
		else if (i != 0 && ((ft_isalnum(str[i]) == 0 && str[i] != '_')))
			return (0);
		i++;
	}
	if (str[i] == '=')
		*env = 1;
	else if (str[i] == '+')
	{
		if (str[i + 1] == '=')
			*env = 2;
		else
			return (0);
	}
	else
		*env = 0;
	return (i);
}

char	**add_env(char **ap, char *str)
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
	new[i] = ft_strdup(str);
	i++;
	new[i] = NULL;
	free(ap);
	return (new);
}

void	check_add_env(t_shell *shell, char *str, int l)
{
	char	*key;

	key = ft_strdup(str);
	key[l] = 0;
	if (search_env(shell->env, key) == NULL)
	{
		if (search_env(shell->exp, key) != NULL)
			shell->exp = delete_env(shell->exp, key);
	}
	else
	{
		shell->env = delete_env(shell->env, key);
	}
	shell->env = add_env(shell->env, str);
	free(key);
}

void	add_export(t_shell *shell, char *str)
{
	int	l;
	int	env;

	l = check_syntax_export(str, &env);
	if (l > 0)
	{
		if (env == 1)
			check_add_env(shell, str, l);
		else if (env == 2)
			check_append_env(shell, str, l);
		else
			if (search_env(shell->env, str) == NULL)
				if (search_env(shell->exp, str) == NULL)
					shell->exp = add_env(shell->exp, str);
	}
	else
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
}

int	builtin_export(t_shell *shell, char **args)
{
	int	i;

	i = 1;
	if (args == NULL || args[1] == NULL)
	{
		print_export(shell);
	}
	else
	{
		while (args[i])
		{
			add_export(shell, args[i]);
			i++;
		}
	}
	return (0);
}
