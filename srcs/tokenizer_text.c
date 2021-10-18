/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 00:46:44 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/19 00:47:30 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    tokenizer_text(t_shell *shell, int *ind, char *str)
{
    int     i;
    char    *l;

    i = *ind;
    l = NULL;
    while(str[i] && !(ft_isset(" <>|\t", str[i])))
    {
        if (str[i] == '\"')
        {
            l = ft_strjoin_part(l, str + *ind, i - *ind);
            i++;
            *ind = i;
            while(str[i] && str[i] != '\"')
            {
                if (str[i] == '$' && !(shell->tokens && ft_tokenlast(shell->tokens)->type == HEREDOC))
                {
                    l = ft_strjoin_part(l, str + *ind, i - *ind);
					i++;
                    *ind = i;
                    l = expand_var_quote(shell, ind, str, l);
                    i = *ind;
                }
                else
                    i++;
            }
             if (str[i] == 0)
            {
                free(l);
                return(1);
            }
            l = ft_strjoin_part(l, str + *ind, i - *ind);
            i++;
            *ind = i;
        }
        else if (str[i] == '\'')
        {
            l = ft_strjoin_part(l, str + *ind, (i - 1) - *ind);
            i++;
            *ind = i;
            while(str[i] != '\'' && str[i] != 0)
                i++;
            if (str[i] == 0)
            {
                free(l);
                return(1);
            }
            l = ft_strjoin_part(l, str + *ind, i - *ind);
            i++;
            *ind = i;
        }
        else if (str[i] == '$')
        {
            if (ft_isset(" \t<>|", str[i + 1]) || str[i + 1] == 0)
            {
                l = ft_strjoin_part(l, str + *ind, (i + 1) - *ind);
                *ind = i + 1;
                ft_token_add_back(&(shell->tokens), ft_tokennew(TEXT, l));
                return(0);
            }
            l = ft_strjoin_part(l, str + *ind, i - *ind);
            i++;
			if(shell->tokens && ft_tokenlast(shell->tokens)->type == HEREDOC)
				continue;
            *ind = i;
			if(shell->tokens && ft_tokenlast(shell->tokens)->type > TEXT && ft_tokenlast(shell->tokens)->type < PIPE)
					l = expand_var_quote(shell, ind, str, l);
			else
            	l = expand_var(shell, ind, str, l);
            i = *ind;
        }
        else
            i++;
    }
    l = ft_strjoin_part(l, str + *ind, i - *ind);
    *ind = i;
    ft_token_add_back(&(shell->tokens), ft_tokennew(TEXT, l));
    return(0);
}