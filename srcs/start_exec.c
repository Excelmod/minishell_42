/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:06:37 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/13 02:26:25 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_builtin_pipe(t_shell *shell, char *str)
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
        i = exit_pipe(shell, shell->cmd->cmds);
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

int     exec_simple_command(t_shell *shell, t_cmd *cmd)
{
    int     pid;
    char    *path_cmd;
    int     ret;

    ret = 0;
	dup2(shell->cmd->fd_in, 0);
	dup2(shell->cmd->fd_out, 1);
    if (check_builtin_simple(shell, shell->cmd->cmds[0]) != -1)
    {
        dup2(shell->stdin, 0);
	    dup2(shell->stdout, 1);
        return(ret);
    }
    signal_process();
	if (search_cmd(shell, cmd->cmds[0], &path_cmd))
	{
    	pid = fork();
    	if (!pid)
    	{
    	    if (execve(path_cmd, cmd->cmds, shell->env) == -1)
			{
				perror("minishell: ");
				return (0) ;
			}
    	}
    	else
            waitpid( pid, &ret, 0);
	}
	free(path_cmd);
    dup2(shell->stdin, 0);
	dup2(shell->stdout, 1);
    return (ret);
}

int    execution(t_shell *shell)
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
		return (exec_simple_command(shell, cmd)); // a changer par la fonction pour gerer le cas de plusieurs commandes avec pipes.
	return (0);
}
