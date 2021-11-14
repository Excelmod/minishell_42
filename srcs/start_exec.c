/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:58:01 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/11/14 17:46:33 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(t_shell *shell, char *str)
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
	search_cmd(shell, cmd, cmd->cmds[0]);
	if (cmd->str)
	{
		pid = fork();
		if (!pid)
		{
			if (execve(cmd->str, cmd->cmds, shell->env) == -1)
			{
				perror("minishell: ");
				return (0);
			}
		}
		else
			waitpid(pid, &ret, 0);
	}
	free(cmd->str);
	cmd->str = NULL;
	return (ret);
}

void close_all_fd(t_shell *shell)
{
	t_cmd *cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		wait(cmd->pid);
		close(cmd->fd_in);
		close(cmd->fd_out);
		cmd = cmd->next;
	}
}

/**
 * @brielf 
 * 
 * @param shell 
 * @param cmd 
 * @param i : command number, allows 
 * @return 0 unless trouble ()
 */
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
		if (ret != -1)
			return (ret);
		search_cmd(shell, cmd, cmd->cmds[0]);
		printf("running : %s\n", cmd->str);
		pid = fork();
		if (!pid)
		{
			if (execve(cmd->str, cmd->cmds, shell->env) == -1)
			{
				perror("minishell: ");
				return (0);
			}
			else
				waitpid(pid, &ret, 0);
		}
		cmd->PID_val = pid;
		cmd = cmd->next;
		i++;
	}
	close_all_fd(shell);
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
	dup2(cmd->fd_out, STDOUT_FILENO);
	ret = check_builtin(shell, shell->cmd->cmds[0]);
	write(STDOUT_FILENO, &(cmd->str), ft_strlen(cmd->str));
	printf("running : %s\n", cmd->str);
	if (ret != -1)
		return (ret);
	search_cmd(shell, cmd, cmd->cmds[0]);
	pid = fork();
	if (!pid)
	{
		if (execve(cmd->str, cmd->cmds, shell->env) == -1)
		{
			perror("minishell: ");
			return (0);
		}
		else
			waitpid(pid, &ret, 0);
	}
	if (ret != -1)
		return (ret);
	dup2(shell->stdin, STDIN_FILENO);
	dup2(shell->stdout, STDOUT_FILENO);
	free(cmd->str);
	cmd->str = NULL;
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
