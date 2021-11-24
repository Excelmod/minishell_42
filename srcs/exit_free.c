/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:50:00 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/20 00:30:39 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	tmp = NULL;
	while (cmd)
	{
		free(cmd->msg_error);
		i = 0;
		while (cmd->cmds && cmd->cmds[i])
		{
			free(cmd->cmds[i]);
			i++;
		}
		free(cmd->cmds);
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
		if (cmd->fd_out != -1)
			close(cmd->fd_out);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
		tmp = NULL;
	}
}

void	ft_tokenclear(t_token **lst)
{
	t_token	*pnt1;
	t_token	*pnt2;

	if (!lst)
		return ;
	pnt1 = *lst;
	pnt2 = pnt1;
	while (pnt1 != NULL)
	{
		pnt1 = pnt1->next;
		free(pnt2->line);
		free(pnt2);
		pnt2 = pnt1;
	}
	*lst = NULL;
}

char	**ft_freetabs(char **t)
{
	int	i;

	i = 0;
	while (t && t[i] != NULL)
	{
		free(t[i]);
		t[i] = NULL;
		i++;
	}
	free(t);
	t = NULL;
	return (NULL);
}

void	exit_free(t_shell *shell, int status)
{
	dup2(shell->stdin, 0);
	dup2(shell->stdout, 1);
	ft_tokenclear(&(shell->tokens));
	free_cmd(shell->cmd);
	shell->path = ft_freetabs(shell->path);
	shell->env = ft_freetabs(shell->env);
	shell->exp = ft_freetabs(shell->exp);
	free(shell->pipes);
	free(shell->pid);
	free(shell->pwd);
	free(shell->str);
	close(shell->stdin);
	close(shell->stdout);
	close(2);
	close(1);
	close(0);
	free(shell);
	rl_clear_history();
	exit(status);
}
