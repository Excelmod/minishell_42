/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:35:54 by lchristo          #+#    #+#             */
/*   Updated: 2021/10/05 14:25:37 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    display_struct(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;

    cmd = shell->cmd;
    while (cmd != NULL)
    {
        i = 0;
        while (cmd->cmds[i] != NULL)
        {
            printf("cmds[%d]: %s\n", i, cmd->cmds[i]);
            i++;
        }
        printf("fd_in = %d\n", cmd->fd_in);
        printf("fd_out = %d\n", cmd->fd_out);
        cmd = cmd->next;
    }
    i = 0;
    while (shell->env[i] != NULL)
    {
        printf("en:%s\n", shell->env[i]);
        i++;
    }
    i = 0;
    while (shell->path[i] != NULL)
    {
        printf("path:%s\n", shell->path[i]);
        i++;
    }
}
