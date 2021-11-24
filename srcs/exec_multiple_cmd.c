/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 00:44:59 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/16 01:12:17 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < (shell->nb_cmds - 1))
	{
		close(shell->pipes[2 * i]);
		close(shell->pipes[(2 * i) + 1]);
		i++;
	}
}

void	exec_pipe(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < shell->nb_cmds)
	{
		exec_command_pipe(shell, cmd, i);
		cmd = cmd->next;
		i++;
	}
	close_pipes(shell);
	i = 0;
	while (i < shell->nb_cmds)
	{
		if (i != shell->nb_cmds - 1)
			waitpid(shell->pid[i], NULL, 0);
		else
			waitpid(shell->pid[i], &(ret), 0);
		i++;
	}
	shell->exit_status = WEXITSTATUS(ret);
}

void	exec_multiple_cmd(t_shell *shell, t_cmd *cmd)
{
	int	nb_pipes;
	int	i;

	nb_pipes = shell->nb_cmds - 1;
	i = 0;
	shell->exit_status = 0;
	shell->pipes = malloc(sizeof(int) * (nb_pipes) * 2);
	shell->pid = malloc(sizeof(int) * shell->nb_cmds);
	while (i < nb_pipes)
	{
		pipe(shell->pipes + (2 * i));
		i++;
	}
	exec_pipe(shell, cmd);
	free(shell->pipes);
	free(shell->pid);
	shell->pid = NULL;
	shell->pipes = NULL;
}
