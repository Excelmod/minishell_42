/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:11:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/25 02:03:55 by ljulien          ###   ########.fr       */
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

t_token	*ft_tokennew(enum types type, char *line)
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
		pnt = ft_token_last(*atoken);
		pnt->next = new;
	}
	else if (!*atoken && atoken && new)
	{
		*atoken = new;
		(*atoken)->next = NULL;
	}
}

void tokenizer_text(t_shell *shell, int *ind, char *line)
{
    int i;

    i = *ind;
    
    *ind = i;
}

void tokenizer_redir_in(t_shell *shell, int *ind, char *line)
{
    return ;
}

void tokenizer_redir_out(t_shell *shell, int *ind, char *line)
{
    return ;
}

    tokenizer(t_shell *shell, char *line)
{
    int i;    

    i = 0;
    while (line[i])
    {
        while(line[i] == ' ' || line[i] == '\t')
            i++;
        if (line[i] == '|')
        {
            ft_token_add_back(&(shell->tokens), ft_tokennew(PIPE, NULL));
            i++;
        }
        else if(line[i] == '>')
            tokenizer_redir_out(shell, &i, line);
        else if(line[i] == '<')
            tokenizer_redir_in(shell, &i, line);
        else
            tokenizer_text(shell, &i, line);        
    }
}