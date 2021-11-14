/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:11:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/14 17:17:52 by adu-pavi         ###   ########.fr       */
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

int	tokenizer(t_shell *shell, t_cmd *cmd, char *line)
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
			error = tokenizer_text(shell, &i, line, cmd);
		}
	}
	return (error);
}
