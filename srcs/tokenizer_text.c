/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 00:46:44 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/22 00:37:52 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*wrap_strjoin_inc(char *str, int *i, int *ind, char *l)
{
		l = ft_strjoin_part(l, str + *ind, *i - *ind);
        (*i)++;
        *ind = *i;
		return (l);
}

char	*text_double(t_shell* shell, int *ind, int *i, char *l)
{
		char	*str;

		str = shell->str;
		l = wrap_strjoin_inc(str, i, ind, l);
        while(str[*i] && str[*i] != '\"')
        {
            if (str[*i] == '$' && !(shell->tokens && ft_tokenlast(shell->tokens)->type == HEREDOC))
            {
                l = wrap_strjoin_inc(str, i, ind, l);
                l = expand_var_quote(shell, ind, str, l);
                *i = *ind;
            }
            else
                (*i)++;
        }
         if (str[*i] == 0)
        {
            free(l);
            return (NULL);
        }
        l = wrap_strjoin_inc(str, i, ind, l);
		return (l);
} 

char	*text_simple(t_shell* shell, int *ind, int *i, char *l)
{
	char	*str;

	str = shell->str;
	l = wrap_strjoin_inc(str, i, ind, l);
    while(str[*i] != '\'' && str[*i] != 0)
        (*i)++;
    if (str[*i] == 0)
    {
        free(l);
        return(NULL);
    }
    l = wrap_strjoin_inc(str, i, ind, l);
	return (l);
}

char	*text_dollar(t_shell* shell, int *ind, int *i, char *l)
{
	char	*str;

	str = shell->str;
	if (ft_isset(" \t<>|", str[i + 1]) || str[i + 1] == 0)
    {
		i++;
        return(NULL);
    }
    l = wrap_strjoin_inc(str, &i, ind, l);
	if(shell->tokens && ft_tokenlast(shell->tokens)->type == HEREDOC)
		continue ;
	if(shell->tokens && ft_tokenlast(shell->tokens)->type > TEXT && ft_tokenlast(shell->tokens)->type < PIPE)
			l = expand_var_quote(shell, ind, str, l);
	else
    	l = expand_var(shell, ind, str, l);
    i = *ind;
	return (l);
}

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
            l = wrap_strjoin_inc(str, &i, ind, l);
            while(str[i] && str[i] != '\"')
            {
                if (str[i] == '$' && !(shell->tokens && ft_tokenlast(shell->tokens)->type == HEREDOC))
                {
                    l = wrap_strjoin_inc(str, &i, ind, l);
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
            l = wrap_strjoin_inc(str, &i, ind, l);
        }
        else if (str[i] == '\'')
        {
            l = wrap_strjoin_inc(str, &i, ind, l);
            while(str[i] != '\'' && str[i] != 0)
                i++;
            if (str[i] == 0)
            {
                free(l);
                return(1);
            }
            l = wrap_strjoin_inc(str, &i, ind, l);
        }
        else if (str[i] == '$')
        {
            if (ft_isset(" \t<>|", str[i + 1]) || str[i + 1] == 0)
            {
				i++;
                break ;
            }
            l = wrap_strjoin_inc(str, &i, ind, l);
			if(shell->tokens && ft_tokenlast(shell->tokens)->type == HEREDOC)
				continue ;
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
    return (0);
}
