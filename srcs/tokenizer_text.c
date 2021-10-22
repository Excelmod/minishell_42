/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 00:46:44 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/22 21:30:54 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*wrap_strjoin_inc(char *str, int *i, int *ind, char *l)
{
	l = ft_strjoin_part(l, str + *ind, *i - *ind);
	(*i)++;
	*ind = *i;
	return (l);
}

int	text_double(t_shell *shell, int *ind, int *i, char **l)
{
	char	*str;

	str = shell->str;
	*l = wrap_strjoin_inc(str, i, ind, *l);
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$' && !(shell->tokens
				&& ft_tokenlast(shell->tokens)->type == HEREDOC))
		{
			*l = wrap_strjoin_inc(str, i, ind, *l);
			*l = expand_var_quote(shell, ind, str, *l);
			*i = *ind;
		}
		else
			(*i)++;
	}
	if (str[*i] == 0)
		return (1);
	*l = wrap_strjoin_inc(str, i, ind, *l);
	return (0);
}

int	text_simple(t_shell *shell, int *ind, int *i, char **l)
{
	char	*str;

	str = shell->str;
	*l = wrap_strjoin_inc(str, i, ind, *l);
	while (str[*i] != '\'' && str[*i] != 0)
		(*i)++;
	if (str[*i] == 0)
	{
		return (1);
	}
	*l = wrap_strjoin_inc(str, i, ind, *l);
	return (0);
}

int	text_dollar(t_shell *shell, int *ind, int *i, char **l)
{
	char	*str;

	str = shell->str;
	if (ft_isset(" \t<>|", str[*i + 1]) || str[*i + 1] == 0)
	{
		(*i)++;
		return (0);
	}
	*l = wrap_strjoin_inc(str, i, ind, *l);
	if (shell->tokens && ft_tokenlast(shell->tokens)->type == HEREDOC)
		return (0);
	if (shell->tokens && ft_tokenlast(shell->tokens)->type > TEXT
		&& ft_tokenlast(shell->tokens)->type < PIPE)
		*l = expand_var_quote(shell, ind, str, *l);
	else
		*l = expand_var(shell, ind, str, *l);
	*i = *ind;
	return (0);
}

int	tokenizer_text(t_shell *shell, int *ind, char *str)
{
	int		i;
	int		error;
	char	*l;

	i = *ind;
	l = NULL;
	error = 0;
	while (str[i] && !(ft_isset(" <>|\t", str[i])))
	{
		if (str[i] == '\"')
			error = text_double(shell, ind, &i, &l);
		else if (str[i] == '\'')
			error = text_simple(shell, ind, &i, &l);
		else if (str[i] == '$')
			error = text_dollar(shell, ind, &i, &l);
		else
			i++;
	}
	l = ft_strjoin_part(l, str + *ind, i - *ind);
	*ind = i;
	ft_token_add_back(&(shell->tokens), ft_tokennew(TEXT, l));
	return (error);
}
