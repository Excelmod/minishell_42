/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 00:02:34 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/19 00:05:17 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_part(char *s1, char *spart, int l)
{
	char	*dest;
	int		l1;

	dest = NULL;
	if (l < 1)
		return (s1);
	l1 = 0;
	if (s1)
	{
		l1 = ft_strlen(s1);
	}
	dest = malloc(sizeof(*dest) * (l1 + l + 1));
	if (spart != NULL && dest != NULL)
	{
		if (s1)
			ft_strlcpy(dest, s1, l1 + 1);
		ft_strlcpy(dest + l1, spart, l + 1);
	}
	free(s1);
	return (dest);
}

char	*sub_expand_var(t_shell *shell, char *str, char *l)
{
	char	**tab;
	int		i;

	tab = NULL;
	tab = ft_split(str, ' ');
	if (!tab || tab[0] == NULL)
	{
		free(tab);
		return (l);
	}
	l = ft_strjoin_part(l, tab[0], ft_strlen(tab[0]));
	i = 1;
	while (tab[i])
	{
		ft_token_add_back(&(shell->tokens), ft_tokennew(TEXT, l));
		l = ft_strdup(tab[i]);
		i++;
	}
	ft_freetabs(tab);
	return (l);
}

char	*expand_exit_status(t_shell *shell, int *ind, char *l)
{
	char	*nb;

	(*ind)++;
	nb = ft_itoa(shell->exit_status);
	l = ft_strjoin_part(l, nb, ft_strlen(nb));
	free(nb);
	return (l);
}

char	*expand_var(t_shell *shell, int *ind, char *str, char *l)
{
	int		i;
	char	*env;
	char	*value;

	i = *ind;
	if (ft_isdigit(str[*ind]))
	{
		(*ind)++;
		return (l);
	}
	else if (str[i] == '?')
		return (expand_exit_status(shell, ind, l));
	else if (ft_isalpha(str[*ind]) == 0 && str[i] != '_')
		return (l);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	env = malloc(sizeof(char) * ((i - *ind) + 1));
	ft_strlcpy(env, str + *ind, (i - *ind) + 1);
	value = env_value(shell->env, env);
	free(env);
	*ind = i;
	if (value)
		l = sub_expand_var(shell, value, l);
	free(value);
	return (l);
}

char	*expand_var_quote(t_shell *shell, int *ind, char *str, char *l)
{
	int		i;
	char	*env;
	char	*value;

	i = *ind;
	if (ft_isdigit(str[*ind]))
	{
		(*ind)++;
		return (l);
	}
	else if (str[i] == '?')
		return (expand_exit_status(shell, ind, l));
	else if (ft_isalpha(str[*ind]) == 0 && str[i] != '_')
		return (l);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	env = malloc(sizeof(char) * ((i - *ind) + 1));
	ft_strlcpy(env, str + *ind, (i - *ind) + 1);
	value = env_value(shell->env, env);
	free(env);
	*ind = i;
	if (value)
		l = ft_strjoin_part(l, value, ft_strlen(value));
	free(value);
	return (l);
}
