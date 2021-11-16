/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 01:02:12 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/16 01:44:25 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin_pipe(t_shell *shell, t_cmd *cmd, char *str)
{
	int	i;

	i = -1;
	if (compare(str, "echo"))
		i = builtin_echo(cmd->cmds);
	else if (compare(str, "env"))
		i = builtin_env(shell);
	else if (compare(str, "export"))
		i = builtin_export(shell, cmd->cmds);
	else if (compare(str, "unset"))
		i = builtin_unset(shell, cmd->cmds);
	else if (compare(str, "pwd"))
		i = builtin_pwd(shell);
	else if (compare(str, "cd"))
		i = builtin_cd(shell, cmd->cmds);
	else if (compare(str, "exit"))
		i = exit_pipe(shell, cmd->cmds);
	return (i);
}

void	clean_pipe_fd(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = shell->cmd;
	while (i < (shell->nb_cmds - 1))
	{
		close(shell->pipes[2 * i]);
		close(shell->pipes[(2 * i) + 1]);
		i++;
	}
	free(shell->pipes);
	free(shell->pid);
	shell->pid = NULL;
	shell->pipes = NULL;
	while (cmd)
	{
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
		if (cmd->fd_out != -1)
			close(cmd->fd_out);
		cmd = cmd->next;
	}
}

void	exec_command_sub(t_shell *shell, t_cmd *cmd)
{
	char	*path_cmd;
	int		ret;

	ret = 0;
	if (cmd->msg_error != NULL)
	{
		ft_putendl_fd(cmd->msg_error, 2);
		exit(1);
	}
	ret = check_builtin_pipe(shell, cmd, cmd->cmds[0]);
	if (ret == -1)
	{
		ret = search_cmd(shell, cmd->cmds[0], &path_cmd);
		if (ret == 1)
		{
			if (execve(path_cmd, cmd->cmds, shell->env) == -1)
			{
				perror("minishell: ");
				ret = errno;
			}
		}
		free(path_cmd);
	}
	exit(ret);
}

void	exec_command_pipe(t_shell *shell, t_cmd *cmd, int nb)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (nb != 0)
			dup2(shell->pipes[2 * (nb - 1)], 0);
		if (nb != (shell->nb_cmds - 1))
			dup2(shell->pipes[(2 * nb) + 1], 1);
		if (cmd->fd_in != -1)
			dup2(cmd->fd_in, 0);
		if (cmd->fd_out != -1)
			dup2(cmd->fd_out, 1);
		clean_pipe_fd(shell);
		exec_command_sub(shell, cmd);
	}
	else
	{
		shell->pid[nb] = pid;
	}
}
