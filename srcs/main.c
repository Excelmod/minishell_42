/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:35:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/22 18:18:41 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_path(t_shell *shell)
{
	char	*tmp;

	shell->path = ft_freetabs(shell->path);
	tmp = env_value(shell->env, "PATH");
	shell->path = ft_split(tmp, ':');
	free(tmp);
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	loop(t_shell *shell)
{
	char	*line;

	line = NULL;
	line = readline("minishell$ ");
	while (line != NULL)
	{
		signal_ignore();
		add_history(line);
		line = parsing_tokenizer(shell, line);
		handle_path(shell);
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
	ft_putendl_fd("exit", 2);
	exit_free(shell, 0);
	return (0);
}
