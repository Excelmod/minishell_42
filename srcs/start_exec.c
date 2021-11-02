/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:06:37 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/02 18:20:05 by ljulien          ###   ########.fr       */
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

int     exec_simple_command(t_shell *shell)
{
    int i;
    int pid;
    int ret;
    char *str;

    i = 0;
	dup2(shell->cmd->fd_in, 0);
	dup2(shell->cmd->fd_out, 1);
    ret = check_builtin(shell, shell->cmd->cmds[0]);
	dup2(shell->stdin, 0);
	dup2(shell->stdout, 1);
    if (ret != -1)
    {
        return(ret);
    }
    pid = fork();
    if (!pid)
    {
        str = ft_strjoin("/", shell->cmd->cmds[0]);
        while (shell->path[i] != NULL)
        {
            execve(ft_strjoin(shell->path[i], str), shell->cmd->cmds, shell->env);
            i++;
        }
        execve(ft_strjoin("./", str), shell->cmd->cmds, shell->env);
        printf("minishell: %s: command not found\n", shell->cmd->cmds[0]);
        exit (1);
    }
    else
    {
        waitpid( pid, &ret, 0);
    }
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
        return (exec_simple_command(shell));
	else if (cmd->cmds) 
		return (exec_simple_command(shell)); // a changer par la fonction pour gerer le cas de plusieurs commandes avec pipes.
	return (0);
}
