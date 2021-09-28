/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:11:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/28 22:00:20 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd   *new_struct_cmd(t_cmd *prev)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    cmd->prev = prev;
    cmd->fd_in = -1;
    cmd->fd_out = -1;
    cmd->cmds = NULL;
    cmd->next = NULL;
    return (cmd);
}

void	parsing(t_shell *shell)
{
    shell->cmd = new_struct_cmd(NULL);
}