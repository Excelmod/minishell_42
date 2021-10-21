/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 20:03:59 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/22 00:13:07 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msg_err_syntax_type(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token == NULL)
		ft_putendl_fd("newline'", 2);
	else if (token->type == PIPE)
		ft_putendl_fd("|'", 2);
	else if (token->type == TRUNC)
		ft_putendl_fd(">'", 2);
	else if (token->type == APPEND)
		ft_putendl_fd(">>'", 2);
	else if (token->type == INPUT)
		ft_putendl_fd("<'", 2);
	else if (token->type == HEREDOC)
		ft_putendl_fd("<<'", 2);
	return (1);
}

int	check_syntax_error_loop(t_token *token, int *error)
{
	int	hdoc_count;

	hdoc_count = 0;
	while (token)
	{
		if (token->type > TEXT && token->type < PIPE
			&& (token->next == NULL || token->next->type != TEXT))
		{
			*error = msg_err_syntax_type(token->next);
			break ;
		}
		else if (token->type == PIPE && (token->next == NULL
				|| token->next->type == PIPE))
		{
			*error = msg_err_syntax_type(token->next);
			break ;
		}
		else if (token->type == HEREDOC)
			hdoc_count++;
		else if (token->next == NULL && *error)
			*error = msg_err_syntax_type(token->next);
		token = token->next;
	}
	return (hdoc_count);
}

int	check_syntax_error(t_shell *shell, int error)
{
	int		hdoc_count;
	t_token	*token;

	hdoc_count = 0;
	token = shell->tokens;
	if (token && token->type == PIPE)
		error = msg_err_syntax_type(token);
	else
	{
		hdoc_count = check_syntax_error_loop(token, &error);
	}
	if (token == NULL && error)
		error = msg_err_syntax_type(token);
	if (hdoc_count)
		handle_error_heredoc(shell, hdoc_count);
	return (error);
}
