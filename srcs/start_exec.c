/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:06:37 by lchristo          #+#    #+#             */
/*   Updated: 2021/10/29 23:56:34 by ljulien          ###   ########.fr       */
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
    return (i);
}

int     path(t_shell *shell)
{
    int i;
    int pid;
    int ret;
    char *str;

    i = 0;
    ret = check_builtin(shell, shell->cmd->cmds[0]);
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
        waitpid( pid, NULL, 0);
    }
    return (0);
}

void    print_error(t_shell *shell)
{
    ft_putendl_fd(shell->cmd->msg_error, 2);
    free(shell->cmd->msg_error);
}

void    starting_execution(t_shell *shell)
{
    if (shell->cmd->msg_error != NULL)
    {
        print_error(shell);
        return ;
    }
    if (shell->cmd->cmds && compare(shell->cmd->cmds[0], "exit"))
        exit (0);
    if (shell->cmd->cmds)
        path(shell);
}
