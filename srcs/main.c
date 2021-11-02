/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:35:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/02 18:07:49 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop(t_shell *shell)
{
	char 	*line;

	line = NULL;
	line = readline("minishell$ ");
	while(line != NULL)
	{
		if (line[0] == EOF) // ctrl D
			return ;
		add_history(line);
		line = parsing_tokenizer(shell, line); // fonction regroupant toute les fonctions parsing et tokenization,  qui free line et retourne NULL,
		if (shell->cmd)
			starting_execution(shell);
		int i = 0;
		t_cmd	*cmd = shell->cmd;
		t_cmd	*tmp = NULL;
		while(cmd)
		{
			free(cmd->msg_error);
			i = 0;
			while(cmd->cmds && cmd->cmds[i])
			{
				free(cmd->cmds[i]);
				i++;
			}
			close(cmd->fd_in);
			close(cmd->fd_out);
			tmp  = cmd;
			cmd = cmd->next;
			free(tmp);
			tmp = NULL;
		}
		shell->cmd = NULL;
		line = readline("minishell$ ");
	}
	
}

int	main(int ac, char **av, char **ap)
{
	t_shell	*sh;

	sh = NULL;
	if (ac && av)
	sh = malloc(sizeof(t_shell));
	if (sh == NULL)
	{
		perror("shell");
		exit(0);
	}
	initialization_shell(sh, ap);
	loop(sh);
	exit_free(sh);
	return (0);
}
