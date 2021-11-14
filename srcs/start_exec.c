/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:06:37 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/14 03:16:53 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_builtin_pipe(t_shell *shell, t_cmd *cmd, char *str)
{
    int i;

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

int     check_builtin_simple(t_shell *shell, char *str)
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
        i = exit_shell(shell, shell->cmd->cmds);
    return (i);
}

void	exec_simple_command(t_shell *shell, t_cmd *cmd)
{
    int     pid;
    char    *path_cmd;
    int     ret;

    ret = 0;
    if (shell->cmd->msg_error != NULL)
    {
        ft_putendl_fd(shell->cmd->msg_error, 2);
		shell->exit_status = 1;
        return;
    }
	dup2(shell->cmd->fd_in, 0);
	dup2(shell->cmd->fd_out, 1);
	ret = check_builtin_simple(shell, shell->cmd->cmds[0]);
    if (ret == -1)
    {
    	signal_process();
		if (search_cmd(shell, cmd->cmds[0], &path_cmd))
		{
    		pid = fork();
    		if (!pid)
    		{
    		    if (execve(path_cmd, cmd->cmds, shell->env) == -1)
				{
					perror("minishell: ");
					ret = errno;
				}
    		}
    		else
			{
				waitpid( pid, &ret, 0);
			}
		}
		free(path_cmd);
    }
    shell->exit_status = ret;
}

void	exec_command(t_shell *shell, t_cmd *cmd, t_context *ctx)
{
    int     pid;
    char    *path_cmd;
    int     ret;

    ret = 0;
	pid = fork();
	if (!pid)
	{
		dup2(ctx->fd_out, 1);
		dup2(ctx->fd_in, 0);
		close(ctx->fd_close);
		if (cmd->msg_error != NULL)
    	{
    	    ft_putendl_fd(cmd->msg_error, 2);
			exit(1);
    	}
		dup2(cmd->fd_in, 0);
		dup2(cmd->fd_out, 1);
		ret = check_builtin_pipe(shell, cmd, cmd->cmds[0]);
    	if (ret == -1)
    	{
    		signal_process();
			if (search_cmd(shell, cmd->cmds[0], &path_cmd))
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
}

void     exec_pipe(t_shell *shell, t_cmd *cmd, t_context *ctx)
{
    int			p[2];
    t_context	new_ctx;

	pipe(p);
    if (cmd->next)
    {
        new_ctx = *ctx;
        new_ctx.fd_in = p[0];
		ctx->fd_out = p[1];
		ctx->fd_close = p[0];
        new_ctx.fd_close = p[1];
        exec_pipe(shell, cmd->next, &new_ctx);
    }
    exec_command(shell, cmd, ctx);
	close(ctx->fd_close);
    close(p[0]);
	close(p[1]);
}

void    exec_multiple_cmd(t_shell *shell, t_cmd *cmd)
{
    t_context	ctx;

    ctx.fd_in = shell->stdin;
    ctx.fd_out = shell->stdout;
    ctx.fd_close = -1;
    exec_pipe(shell, cmd, &ctx);
	wait(NULL);
	wait(NULL);
	wait(NULL);
}

void    execution(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
    if (cmd->cmds && cmd->next == NULL)
        exec_simple_command(shell, cmd);
	else if (cmd->cmds) 
		exec_multiple_cmd(shell, cmd);
	dup2(shell->stdin, 0);
	dup2(shell->stdout, 1);
}
