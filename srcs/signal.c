/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:20:06 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/16 00:30:41 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redisplay_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	interrupt_process(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

void	interrupt_heredoc(int signal)
{
	(void)signal;
}

void	signal_heredoc(void)
{
	signal(SIGINT, interrupt_heredoc);
	signal(SIGQUIT, interrupt_heredoc);
}

void	quit_process(int signal)
{
	(void)signal;
	printf("Quit (core dumped)\n");
}

void	signal_input(void)
{
	signal(SIGINT, redisplay_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_process(void)
{
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
}
