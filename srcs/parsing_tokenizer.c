/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:41:03 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/03 18:27:21 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parsing_tokenizer(t_shell *shell , char *line)
{
	int		error;
	/*
    t_token *lst;
	int		i;
	t_cmd	*cmd;
    */

	error = tokenizer(shell, line);
	/*
    lst = shell->tokens;
	while(lst)
	{
		printf("le type est %s et la ligne est :%s\n", type_str[(int)(lst->type)], lst->line);
		lst = lst->next;
	}
    */
	error = check_syntax_error(shell, error);
	if(!error)
		parsing(shell);
	free(line);
	ft_tokenclear(&(shell->tokens));
	/*cmd = shell->cmd;
    while(cmd)
	{
		i = 0;
		printf("le input fd est %d et le output fd est %d\n", cmd->fd_in, cmd->fd_out);
		while(cmd->cmds && cmd->cmds[i])
		{
			printf("ARG %d = %s  ", i + 1, cmd->cmds[i]);
			i++;
		}
		if (cmd->fd_in != -1)
		{
			char *str;
			str =NULL;
			printf("HEREDOC:\n");
			while(get_next_line(cmd->fd_in, &str))
			{
				printf("%s\n", str);
			}
		}
		printf("\n\n");
		cmd = cmd->next;
	}
	builtin_env(shell);
    */
	return(NULL);
}
