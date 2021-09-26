/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:11:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/26 18:39:17 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_strjoin_part(char *s1, char *spart, int l)
{
	char	*dest;
	int		l1;

	dest = NULL;
    if (l < 1)
        return (s1);
    l1 = 0;
    if (s1)
        l1 = ft_strlen(s1);
	dest = malloc(sizeof(*dest) * (l1 + l + 1));
	if (spart != NULL && dest != NULL)
	{
        if (s1)
		    ft_strlcpy(dest, s1, l1 + 1);
		ft_strlcpy(dest + l1, spart, l + 1);
	}
    free(s1);
	return (dest);
}

char    *tokenizer_text(t_shell *shell, int *ind, char *str)
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

                i++;
            }
             if (str[i] == 0)
            {
                free(l);
                exit_message_error(shell, "Minishell: Syntax error");
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
                exit_message_error(shell, "Minishell: Syntax error");
            }
            l = ft_strjoin_part(l, str + *ind, i - *ind);
            i++;
            *ind = i;
        }
        else
            i++;
    }
    printf("la phrase est %s\n", str + *ind);
    l = ft_strjoin_part(l, str + *ind, i - *ind);
    i++;
    *ind = i;
    return (l);
}

void tokenizer_redir_in(t_shell *shell, int *ind, char *str)
{
    (*ind)++;
    if (str[*ind] == '<')
    {
        (*ind)++;
        if (ft_isset("<>|",str[*ind]))
            exit_message_error(shell, "Minishell: Syntax error");
        while(str[*ind] == ' ' || str[*ind] == '\t')
            (*ind)++;
        if (ft_isset("<>|",str[*ind]))
            exit_message_error(shell, "Minishell: Syntax error");
        ft_token_add_back(&(shell->tokens), ft_tokennew(HEREDOC, tokenizer_text(shell, ind, str)));
    }
    else if (!(ft_isset(">|",str[*ind])))
    {
        while(str[*ind] == ' ' || str[*ind] == '\t')
            (*ind)++;
        if (ft_isset("<>|",str[*ind]))
            exit_message_error(shell, "Minishell: Syntax error");
        ft_token_add_back(&(shell->tokens), ft_tokennew(INPUT, tokenizer_text(shell, ind, str)));
    }
    else
        exit_message_error(shell, "Minishell: Syntax error");
}

void tokenizer_redir_out(t_shell *shell, int *ind, char *str)
{
    (*ind)++;
    if (str[*ind] == '>')
    {
        (*ind)++;
        if (ft_isset("<>|",str[*ind]))
            exit_message_error(shell, "Minishell: Syntax error");
        while(str[*ind] == ' ' || str[*ind] == '\t')
            (*ind)++;
        if (ft_isset("<>|",str[*ind]))
            exit_message_error(shell, "Minishell: Syntax error");
        ft_token_add_back(&(shell->tokens), ft_tokennew(APPEND, tokenizer_text(shell, ind, str)));
    }
    else if (!(ft_isset("<|",str[*ind])))
    {
        while(str[*ind] == ' ' || str[*ind] == '\t')
            (*ind)++;
        if (ft_isset("<>|",str[*ind]))
            exit_message_error(shell, "Minishell: Syntax error");
        ft_token_add_back(&(shell->tokens), ft_tokennew(TRUNC, tokenizer_text(shell, ind, str)));
    }
    else
        exit_message_error(shell, "Minishell: Syntax error");
    return ;
}

void    tokenizer(t_shell *shell, char *line)
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
        else if(line[i])
        {
            ft_token_add_back(&(shell->tokens), ft_tokennew(CMD, tokenizer_text(shell, &i, line)));
        }        
    }
}