/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:41:03 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/14 17:10:20 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parsing_tokenizer(t_shell *shell, t_cmd *cmd, char *line)
{
	int	error;

	cmd->str = line;
	error = tokenizer(shell, cmd, line);
	error = check_syntax_error(shell, error);
	if (!error)
		parsing(shell);
	free(line);
	cmd->str = NULL;
	ft_tokenclear(&(shell->tokens));
	cmd = shell->cmd;
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
		printf("\nmsg_error: '%s'\n", cmd->msg_error);
		printf("fd_in: %d\nfd_out: %d\n", cmd->fd_in, cmd->fd_out);
		cmd = cmd->next;
		if (cmd)
			printf("\nPIPE\n\n");
	}
	printf("\nFIN\n\n");
	return (NULL);
}
