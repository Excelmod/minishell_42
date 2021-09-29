/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:11:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/29 20:21:17 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd   *new_struct_cmd(t_cmd *prev)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    cmd->prev = prev;
    cmd->fd_in = -1;
    cmd->fd_out = -1;
    cmd->cmds = NULL;
    cmd->next = NULL;
    return (cmd);
}

void    switch_fd(t_cmd *cmd, int fd, int io)
{
    if (io)
    {
        if (cmd->fd_out >= 0)
            close(fd);
        cmd->fd_out = fd;
    }
    else
    {
        if (cmd->fd_in >= 0)
            close(fd);
        cmd->fd_in = fd;
    }
}

void    parsing_io_files(t_cmd *cmd, t_token *token)
{
    int fd;

    if(token->type == INPUT)
    {
        fd = open(token->next->line, O_RDONLY);
        switch_fd(cmd, fd, 0);
    }
    else if(token->type == TRUNC)
    {
        fd = open(token->next->line,
			O_WRONLY | O_TRUNC | O_CREAT, S_IWUSR | S_IRUSR);
        switch_fd(cmd, fd, 1);
    }
    else if(token->type == APPEND)
    {
        fd = open(token->next->line,
			O_WRONLY | O_APPEND | O_CREAT, S_IWUSR | S_IRUSR);
        switch_fd(cmd, fd, 1);
    }
    else if(token->type == HEREDOC)
    {
        fd = token->fd;
        switch_fd(cmd, fd, 0);
    }
}

void    parsing_text(t_cmd *cmd, t_token *token)
{
    int     i;
    int     nb;
    char    **tab;

        i = 0;
        nb = 0;
        while(cmd->cmds && cmd->cmds[nb])
            nb++;
        tab = malloc(sizeof(char *) * (nb + 2));
        while(cmd->cmds && i < nb)
        {
            tab[i] = cmd->cmds[i];
            i++;
        }
        tab[i] = ft_strdup(token->line);
        tab[i + 1] = NULL;
        free(cmd->cmds);
        cmd->cmds = tab;
}

void	parsing(t_shell *shell)
{
    t_token *token;
    t_cmd   *lst_cmd;

    token = shell->tokens;
    shell->cmd = new_struct_cmd(NULL);
    lst_cmd = shell->cmd;
    while(token)
    {
        if (token->type > TEXT && token->type < PIPE)
        {
            parsing_io_files(lst_cmd, token);
            token = token->next;
        }
        else if (token->type == TEXT)
            parsing_text(lst_cmd, token);
        else if (token->type == PIPE)
        {
            lst_cmd->next = new_struct_cmd(lst_cmd);
            lst_cmd = lst_cmd->next;
        }
        token = token->next;
    }
}