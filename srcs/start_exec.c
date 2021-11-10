/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:06:37 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/10 18:15:00 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_builtin(t_shell *shell, char *str)
{
	int i;

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
		exit(0);
	return (i);
}

int exec_simple_command(t_shell *shell, t_cmd *cmd)
{
	int pid;
	int ret;

	dup2(shell->cmd->fd_in, 0);
	dup2(shell->cmd->fd_out, 1);
	ret = check_builtin(shell, shell->cmd->cmds[0]);
	dup2(shell->stdin, 0);
	dup2(shell->stdout, 1);
	if (ret != -1)
		return (ret);
	search_cmd(shell, cmd->cmds[0]);
	if (shell->str)
	{
		pid = fork();
		if (!pid)
		{
			if (execve(shell->str, cmd->cmds, shell->env) == -1)
			{
				perror("minishell: ");
				return (0);
			}
		}
		else
			waitpid(pid, &ret, 0);
	}
	free(shell->str);
	shell->str = NULL;
	return (ret);
}

int	exec_multiple_cmd_1(t_shell *shell, t_cmd *cmd, int *i)
{
	int	pid;
	int	ret;

	while (cmd->next)
	{
		if (cmd != shell->cmd)
			dup2(cmd->fd_in, shell->pipe_fd[*i][0]);
		pipe(shell->pipe_fd[*i]);
		dup2(cmd->fd_out, shell->pipe_fd[*i][1]);
		ret = check_builtin(shell, shell->cmd->cmds[0]);
		search_cmd(shell, cmd->cmds[0]);
		pid = fork();
		if (!pid)
		{
			if (execve(shell->str, cmd->cmds, shell->env) == -1)
			{
				perror("minishell: ");
				return (0);
			}
			else
				waitpid(pid, &ret, 0);
		}
		cmd = cmd->next;
		i++;
	}
	return (0);
}

int	exec_multiple_cmd(t_shell *shell, t_cmd *cmd)
{
	int	pid;
	int	i;
	int	ret;

	i = 0;
	dup2(shell->cmd->fd_in, 0);
	exec_multiple_cmd_1(shell, cmd, &i);
	dup2(cmd->fd_in, shell->pipe_fd[i - 1][0]);
	dup2(cmd->fd_out, 1);
	ret = check_builtin(shell, shell->cmd->cmds[0]);
	if (ret != -1)
		return (ret);
	search_cmd(shell, cmd->cmds[0]);
	pid = fork();
	if (!pid)
	{
		if (execve(shell->str, cmd->cmds, shell->env) == -1)
		{
			perror("minishell: ");
			return (0);
		}
		else
			waitpid(pid, &ret, 0);
	}
	if (ret != -1)
		return (ret);
	dup2(shell->stdin, 0);
	dup2(shell->stdout, 1);
	free(shell->str);
	shell->str = NULL;
	return (ret);
}

int	execution(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	if (cmd->msg_error != NULL)
	{
		ft_putendl_fd(shell->cmd->msg_error, 2);
		return (0);
	}
	if (cmd->cmds && cmd->next == NULL)
		return (exec_simple_command(shell, cmd));
	else if (cmd->cmds)
		return (exec_multiple_cmd(shell, cmd));
	return (0);
}
