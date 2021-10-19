/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:21:28 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/19 03:07:29 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	switch_fd(t_cmd *cmd, int fd, int io)
{
	if (io)
	{
		if (cmd->fd_out >= 0)
			close(cmd->fd_out);
		cmd->fd_out = fd;
	}
	else
	{
		if (cmd->fd_in >= 0)
			close(cmd->fd_in);
		cmd->fd_in = fd;
	}
	if (fd < 0)
		return (1);
	return (0);
}

int	parsing_io_files(t_cmd *cmd, t_token *token)
{
	int	fd;
	int	io;

	io = 1;
	fd = -1;
	if (token->type == INPUT || token->type == HEREDOC)
		io = 0;
	if (token->type == INPUT)
		fd = open(token->next->line, O_RDONLY);
	else if (token->type == TRUNC)
		fd = open(token->next->line,
				O_WRONLY | O_TRUNC | O_CREAT, S_IWUSR | S_IRUSR);
	else if (token->type == APPEND)
	{
		fd = open(token->next->line,
				O_WRONLY | O_APPEND | O_CREAT, S_IWUSR | S_IRUSR);
	}
	else if (token->type == HEREDOC)
		fd = token->fd;
	return (switch_fd(cmd, fd, io));
}
