/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:41:03 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/14 15:04:27 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parsing_tokenizer(t_shell *shell, char *line)
{
	int	error;

	shell->str = line;
	error = tokenizer(shell, line);
	error = check_syntax_error(shell, error);
	if (!error)
		parsing(shell);
	free(line);
	shell->str = NULL;
	ft_tokenclear(&(shell->tokens));
	/*t_cmd *cmd = shell->cmd;
	printf("\nFonction dans le fichier parsing_tokenizer.c pour afficher les structures commandes\n");
	printf("\nDEBUT\n\n");
	while (cmd)
	{
		int i = 0;
		printf("Nouvelle CMD:\n");
		while(cmd->cmds && cmd->cmds[i])
		{
			printf("cmd%d: '%s'\n", i+1, cmd->cmds[i]);
			i++;
		}
		printf("%s", shell->cmd->msg_error);
		printf("fd_in: %d\nfd_out: %d\n", cmd->fd_in, cmd->fd_out);
		cmd = cmd->next;
		if (cmd)
			printf("\nPIPE\n\n");
	}
	printf("\nFIN\n\n");*/	
	return (NULL);
}
