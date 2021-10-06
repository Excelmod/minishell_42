/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:50:00 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/06 16:00:31 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exit_free(t_shell *shell)
{
	ft_tokenclear(&(shell->tokens));
	shell->path = ft_freetabs(shell->path);
	shell->env = ft_freetabs(shell->env);
	free(shell);
	exit(0);
}

void	message_error(char *msg)
{
	ft_putendl_fd(msg, 2);
}

void	exit_message_error(t_shell *shell, char *msg)
{
	ft_putendl_fd(msg, 2);
	exit_free(shell);
}