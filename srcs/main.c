/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:35:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/02 21:35:14 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	tmp = NULL;
	while(cmd)
	{
		free(cmd->msg_error);
		i = 0;
		while(cmd->cmds && cmd->cmds[i])
		{
			free(cmd->cmds[i]);
			i++;
		}
		free(cmd->cmds);
		close(cmd->fd_in);
		close(cmd->fd_out);
		tmp  = cmd;
		cmd = cmd->next;
		free(tmp);
		tmp = NULL;
	}
}

void	loop(t_shell *shell)
{
	char 	*line;

	line = NULL;
	line = readline("minishell$ ");
	while(line != NULL)
	{
		add_history(line);
		line = parsing_tokenizer(shell, line); // fonction regroupant toute les fonctions parsing et tokenization,  qui free line et retourne NULL,
		if (shell->cmd)
			shell->exit_status = execution(shell);
		free_cmd(shell->cmd);
		shell->cmd = NULL;
		signal_input();
		line = readline("minishell$ ");
	}
	
}

int	main(int ac, char **av, char **ap)
{
	t_shell	*shell;

	shell = NULL;
	if (ac && av)
	shell = malloc(sizeof(t_shell));
	if (shell == NULL)
	{
		perror("shell");
		exit(0);
	}
	initialization_shell(shell, ap);
	loop(shell);
	exit_free(shell);
	return (0);
}
