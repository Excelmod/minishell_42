/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:11:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/19 00:13:15 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer_redir_in(t_shell *shell, int *ind, char *str)
{
	if (str[*ind + 1] == '<')
	{
		ft_token_add_back(&(shell->tokens), ft_tokennew(HEREDOC, NULL));
		(*ind)++;
	}
	else
		ft_token_add_back(&(shell->tokens), ft_tokennew(INPUT, NULL));
	(*ind)++;
}

void	tokenizer_redir_out(t_shell *shell, int *ind, char *str)
{
	if (str[*ind + 1] == '>')
	{
		ft_token_add_back(&(shell->tokens), ft_tokennew(APPEND, NULL));
		(*ind)++;
	}
	else
		ft_token_add_back(&(shell->tokens), ft_tokennew(TRUNC, NULL));
	(*ind)++;
}

int	tokenizer(t_shell *shell, char *line)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (line[i] && !error)
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '|')
		{
			ft_token_add_back(&(shell->tokens), ft_tokennew(PIPE, NULL));
			i++;
		}
		else if (line[i] == '>')
			tokenizer_redir_out(shell, &i, line);
		else if (line[i] == '<')
			tokenizer_redir_in(shell, &i, line);
		else if (line[i])
		{
			error = tokenizer_text(shell, &i, line);
		}
	}
	return (error);
}
