/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:11:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/06 16:52:59 by ljulien          ###   ########.fr       */
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
    cmd->msg_error = NULL;
    return (cmd);
}

int    switch_fd(t_cmd *cmd, int fd, int io)
{
    if (io)
    {
        if (cmd->fd_out >= 0)
            close(cmd->fd_out);
        cmd->fd_out = fd;
    }
    else
    {
        if (cmd->fd_in >= 0)
            close(cmd->fd_in);
        cmd->fd_in = fd;
    }
    if (fd < 0)
        return(1);
    return (0);
}

int    parsing_io_files(t_cmd *cmd, t_token *token)
{
    int fd;
    int error;

    error = 0;
    if(token->type == INPUT)
    {
        fd = open(token->next->line, O_RDONLY);
        error = switch_fd(cmd, fd, 0);
    }
    else if(token->type == TRUNC)
    {
        fd = open(token->next->line,
			O_WRONLY | O_TRUNC | O_CREAT, S_IWUSR | S_IRUSR);
        error = switch_fd(cmd, fd, 1);
    }
    else if(token->type == APPEND)
    {
        fd = open(token->next->line,
			O_WRONLY | O_APPEND | O_CREAT, S_IWUSR | S_IRUSR);
        error = switch_fd(cmd, fd, 1);
    }
    else if(token->type == HEREDOC)
    {
        fd = token->fd;
        error = switch_fd(cmd, fd, 0);
    }
    return (error);
}

t_token    *open_msg_error(t_cmd *cmd, t_token *token)
{
    char    *str;
    char    *tmp;

    tmp = NULL;
    str = ft_strjoin("minishell: ", token->next->line);
    tmp = str;
    str = ft_strjoin(str, ": ");
    free(tmp);
    tmp = str;
    str = ft_strjoin(str, strerror(errno));
    free(tmp);
    cmd->msg_error = str;
    while (token->next && token->next->type != PIPE)
    {
        if (token->type == HEREDOC)
            close(token->fd);
        token = token->next;
    }
    cmd->cmds = ft_freetabs(cmd->cmds);
    return (token);
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
            if(parsing_io_files(lst_cmd, token))
                token = open_msg_error(lst_cmd, token);
            else
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