/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:06:37 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/16 01:08:12 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin_simple(t_shell *shell, char *str)
{
	int	i;

	i = -1;
	if (compare(str, "echo"))
		i = builtin_echo(shell->cmd->cmds);
	else if (compare(str, "env"))
		i = builtin_env(shell);
	else if (compare(str, "export"))
		i = builtin_export(shell, shell->cmd->cmds);
	else if (compare(str, "unset"))
		i = builtin_unset(shell, shell->cmd->cmds);
	else if (compare(str, "pwd"))
		i = builtin_pwd(shell);
	else if (compare(str, "cd"))
		i = builtin_cd(shell, shell->cmd->cmds);
	else if (compare(str, "exit"))
		i = exit_shell(shell, shell->cmd->cmds);
	return (i);
}

int	simple_command(t_shell *shell, t_cmd *cmd, int ret)
{
	char	*path_cmd;

	ret = check_builtin_simple(shell, shell->cmd->cmds[0]);
	if (ret == -1)
	{
		ret = search_cmd(shell, cmd->cmds[0], &path_cmd);
		if (ret == 1)
		{
			if (fork() == 0)
			{
				if (execve(path_cmd, cmd->cmds, shell->env) == -1)
				{
					perror("minishell: ");
					ret = errno;
				}
			}
			else
			{
				wait(&ret);
				ret = WEXITSTATUS(ret);
			}
		}
		free(path_cmd);
	}
	return (ret);
}

void	exec_simple_command(t_shell *shell, t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (shell->cmd->msg_error != NULL)
	{
		ft_putendl_fd(shell->cmd->msg_error, 2);
		shell->exit_status = 1;
		return ;
	}
	if (shell->cmd->fd_in != -1)
	{
		dup2(shell->cmd->fd_in, 0);
		close(shell->cmd->fd_in);
		shell->cmd->fd_in = -1;
	}
	if (shell->cmd->fd_out != -1)
	{
		dup2(shell->cmd->fd_out, 1);
		close(shell->cmd->fd_out);
		shell->cmd->fd_out = -1;
	}
	shell->exit_status = simple_command(shell, cmd, ret);
}

void	execution(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	shell->nb_cmds = 0;
	while (cmd)
	{
		shell->nb_cmds += 1;
		cmd = cmd->next;
	}
	signal_process();
	cmd = shell->cmd;
	if (shell->nb_cmds == 1)
		exec_simple_command(shell, cmd);
	else if (shell->nb_cmds > 1)
		exec_multiple_cmd(shell, cmd);
	dup2(shell->stdin, 0);
	dup2(shell->stdout, 1);
}
