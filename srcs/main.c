/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:35:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/14 14:58:19 by ljulien          ###   ########.fr       */
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
		add_history(line);
		line = parsing_tokenizer(shell, line);
		if (shell->cmd)
		{
			execution(shell);
		}
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
	exit_free(shell, 0);
	return (0);
}
