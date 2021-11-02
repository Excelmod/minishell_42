/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:06:37 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/02 19:02:03 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_builtin(t_shell *shell, char *str)
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
        exit (0);
    return (i);
}

int     exec_simple_command(t_shell *shell, t_cmd *cmd)
{
    int pid;
    int ret;

	dup2(shell->cmd->fd_in, 0);
	dup2(shell->cmd->fd_out, 1);
    ret = check_builtin(shell, shell->cmd->cmds[0]);
	dup2(shell->stdin, 0);
	dup2(shell->stdout, 1);
    if (ret != -1)
        return(ret);
	search_cmd(shell, cmd->cmds[0]);
	if (shell->str)
	{
    	pid = fork();
    	if (!pid)
    	{
    	    if (execve(shell->str, cmd->cmds, shell->env) == -1)
			{
				perror("minishell: ");
				return (0) ;
			}
    	}
    	else
    	    waitpid( pid, &ret, 0);
	}
	free(shell->str);
	shell->str = NULL;
    return (ret);
}

int    starting_execution(t_shell *shell)
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
