/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 20:03:59 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/28 22:20:46 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_str(void *content)
{
	free((char *)content);
	content = NULL;
}

t_list  *get_heredoc_lines(char *cmp)
{
    char    *line;
    t_list  *lst;
    int     l;
    
    lst = NULL;
    line = NULL;
    l = ft_strlen(cmp);
    handle_prompt_heredoc();
    while(get_next_line(0, &line))
	{
        if (ft_strncmp(line, cmp, l + 1) == 0)
            break;
        ft_lstadd_back(&lst, ft_lstnew((void *)line));
        handle_prompt_heredoc();
    }
    return(lst);
}

void 	handle_error_heredoc(t_shell *shell, int count)
{
    t_token *token;
    t_list  *list;

    token = shell->tokens;
    while (token && count)
    {
        if (token->type == HEREDOC)
        {
            list = get_heredoc_lines(token->next->line);
            ft_lstclear(&list, del_str);
            count--;
        }
        token = token->next;
    }
}

int     msg_err_syntax_type(t_token *token)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    if  (token == NULL)
        ft_putendl_fd("newline'", 2);
    else if(token->type == PIPE)
        ft_putendl_fd("|'", 2);
    else if(token->type == TRUNC)
        ft_putendl_fd(">'", 2);
    else if(token->type == APPEND)
        ft_putendl_fd(">>'", 2);
    else if(token->type == INPUT)
        ft_putendl_fd("<'", 2);
    else if(token->type == HEREDOC)
        ft_putendl_fd("<<'", 2);
    return(1);
}

int 	check_syntax_error(t_shell *shell, int error)
{
    int     hdoc_count;
    t_token *token;

    hdoc_count = 0;
    token = shell->tokens;
    while(token)
    {
        if (token->type > TEXT && token->type < PIPE && (token->next == NULL || token->next->type != TEXT))
        {
            error = msg_err_syntax_type(token->next);
            break;
        }
        else if (token->type == PIPE && (token->next == NULL || token->next->type == PIPE))
        {
            error = msg_err_syntax_type(token->next);
            break;
        }
        else if (token->type == HEREDOC)
            hdoc_count++;
        else if (token->next == NULL && error)
            msg_err_syntax_type(token->next);
        token = token->next;
    }
    if (error && hdoc_count)
        handle_error_heredoc(shell, hdoc_count);
    return(error);
}