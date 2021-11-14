/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:35:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/14 17:07:22 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop(t_shell *shell)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		i;
	char	*line;

	cmd = shell->cmd;
	line = NULL;
	line = readline("minishell$ ");
	while(line != NULL)
	{
		if (line[0] == EOF) // ctrl D
			return ;
		add_history(line);
		line = parsing_tokenizer(shell, cmd, line); // fonction regroupant toute les fonctions parsing et tokenization,  qui free line et retourne NULL,
		if (shell->cmd)
			execution(shell);
		i = 0;
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
