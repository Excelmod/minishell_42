/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:01:16 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/18 22:47:16 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tokenlast(t_token *token)
{
	if (token != NULL)
		while (token->next != NULL)
			token = token->next;
	return (token);
}

t_token	*ft_tokennew(enum e_types type, char *line)
{
	t_token	*new;

	new = malloc(sizeof(*new));
	if (new != NULL)
	{
		new->type = type;
		new->line = line;
		new->next = NULL;
	}
	return (new);
}

void	ft_token_add_back(t_token **atoken, t_token *new)
{
	t_token	*pnt;

	if (*atoken && atoken && new)
	{
		pnt = ft_tokenlast(*atoken);
		pnt->next = new;
	}
	else if (!*atoken && atoken && new)
	{
		*atoken = new;
		(*atoken)->next = NULL;
	}
}
