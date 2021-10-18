/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:24:41 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/18 23:44:57 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *cur_dir_name(void)
{
    int     size;
    char    *buf;

    size = 50;
    buf = malloc(sizeof(char) * size);
    while(getcwd(buf, size) == NULL)
    {
        size += 50;
        free(buf);
        buf = malloc(sizeof(char) * size);
    }
    return(buf);
}

void    handle_prompt(void)
{
    char *cur_dir;

    cur_dir = cur_dir_name();

    write(1, cur_dir, ft_strlen(cur_dir));
    write(1, "$ ", 2);
}

void    handle_prompt_heredoc(void)
{
    write(1, "> ", 2);
}