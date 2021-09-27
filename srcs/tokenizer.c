/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:11:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/27 20:16:18 by ljulien          ###   ########.fr       */
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

void    sub_expand_var(t_shell *shell, char *str, char *l)
{
    char    **tab;
    int     i;

    tab = NULL;
    tab = ft_split(value, ' ');
    if (!tab || tab[0] == NULL)
    {
        free(tab);
        return;
    }
    l = ft_strjoin_part(l, tab[0], ft_strlen(tab[0]));
    i = 1;
    while (tab[i])
    {
        ft_token_add_back(&(shell->tokens), ft_tokennew(TEXT, l));
        l = ft_strdup(tab[i];)
        i++;
    }
    free_tab(tab);
}

void    expand_var(t_shell *shell, int *ind, char *str, char *l)
{
    int     i;
    char    *env;
    char    *value;

    (*ind)++;
    i = *ind;
    if (ft_isdigit(str[*ind]))
    {
        (*ind)++;
        return ;
    }
    else if (ft_isalpha(str[*ind]) == 0)
        return ;
    while (ft_isalnum(str[i]) || str[i] == '_')
        i++;
    env = ft_strlcpy(malloc(sizeof(char) * ((i - *ind) + 1), str + *ind, (i - *ind) + 1);
    value = env_value(shell->env, env);
    free(env);
    *ind = i;
    sub_expand_var(shell, value, l);
    free(value);
}

void    sub_expand_var(t_shell *shell, char *str, char *l)
{
    char    **tab;
    int     i;

    tab = NULL;
    tab = ft_split(value, ' ');
    if (!tab || tab[0] == NULL)
    {
        free(tab);
        return;
    }
    l = ft_strjoin_part(l, tab[0], ft_strlen(tab[0]));
    i = 1;
    while (tab[i])
    {
        ft_token_add_back(&(shell->tokens), ft_tokennew(TEXT, l));
        l = ft_strdup(tab[i];)
        i++;
    }
    free_tab(tab);
}

void    expand_var_quote(t_shell *shell, int *ind, char *str, char *l)
{
    int     i;
    char    *env;
    char    *value;

    (*ind)++;
    i = *ind;
    if (ft_isdigit(str[*ind]))
    {
        (*ind)++;
        return ;
    }
    else if (ft_isalpha(str[*ind]) == 0)
        return ;
    while (ft_isalnum(str[i]) || str[i] == '_')
        i++;
    env = ft_strlcpy(malloc(sizeof(char) * ((i - *ind) + 1), str + *ind, (i - *ind) + 1);
    value = env_value(shell->env, env);
    free(env);
    *ind = i;
    l = ft_strjoin_part(l, value, ft_strlen(value));
    free(value);
}

void    tokenizer_text(t_shell *shell, int *ind, char *str)
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
                if (str[i] == '$')
                {
                    l = ft_strjoin_part(l, str + *ind, i - *ind);
                    *ind = i;
                    expand_var_quote(shell, ind, str, l);
                }
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
        else if (str[i] == '$')
        {
            if (ft_isset(" \t<>|", str[i + 1])))
            {
                l = ft_strjoin_part(l, str + *ind, (i + 1) - *ind);
                *ind = i + 1;
                ft_token_add_back(&(shell->tokens), ft_tokennew(TEXT, l));
                return ;
            }
            l = ft_strjoin_part(l, str + *ind, i - *ind);
            *ind = i;
            expand_var(shell, ind, str, l);
        }
        else
            i++;
    }
    printf("la phrase est %s\n", str + *ind);
    l = ft_strjoin_part(l, str + *ind, i - *ind);
    i++;
    *ind = i;
    ft_token_add_back(&(shell->tokens), ft_tokennew(TEXT, l));
}

void tokenizer_redir_in(t_shell *shell, int *ind, char *str)
{
   if (str[*ind + 1] == '<')
    {
        ft_token_add_back(&(shell->tokens), ft_tokennew(HEREDOC, NULL));
        (*ind)++;
    }
    else
        ft_token_add_back(&(shell->tokens), ft_tokennew(INPUT, NULL));
    (*ind)++
}

void tokenizer_redir_out(t_shell *shell, int *ind, char *str)
{
    if (str[*ind + 1] == '>')
    {
        ft_token_add_back(&(shell->tokens), ft_tokennew(APPEND, NULL));
        (*ind)++;
    }
    else
        ft_token_add_back(&(shell->tokens), ft_tokennew(TRUNC, NULL));
    (*ind)++
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
            tokenizer_text(shell, &i, line)));
        }        
    }
}