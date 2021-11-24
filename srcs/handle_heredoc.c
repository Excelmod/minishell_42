/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 23:52:07 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/24 18:35:50 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_str(void *content)
{
	free((char *)content);
	content = NULL;
}

void	heredoc_eof(t_shell *shell, char *line, char *cmp)
{
	int	i;

	i = shell->nbline;
	printf("bash: warning: here-document at line %d", i);
	printf(" delimited by end-of-file (wanted `%s')\n", cmp);
	free(line);
}

t_list	*get_heredoc_lines(t_shell *shell, char *cmp)
{
	char	*line;
	t_list	*lst;
	int		l;

	lst = NULL;
	line = NULL;
	l = ft_strlen(cmp);
	line = readline("> ");
	while (line && !g_signal)
	{
		if (ft_strncmp(line, cmp, l + 1) == 0)
		{
			free(line);
			return (lst);
		}
		ft_lstadd_back(&lst, ft_lstnew((void *)line));
		line = readline("> ");
	}
	if (g_signal)
		free(line);
	else if (line && *line)
		ft_lstadd_back(&lst, ft_lstnew((void *)line));
	else
		heredoc_eof(shell, line, cmp);
	return (lst);
}

void	write_heredoc(t_list *list, t_token *token)
{
	int	fd;

	fd = open("/tmp/.minishell_heredoc",
			O_WRONLY | O_TRUNC | O_CREAT, S_IWUSR | S_IRUSR);
	while (list)
	{
		ft_putendl_fd((char *)(list->content), fd);
		list = list->next;
	}
	close(fd);
	fd = open("/tmp/.minishell_heredoc", O_RDONLY);
	unlink("/tmp/.minishell_heredoc");
	token->fd = fd;
	token->next->fd = fd;
}

void	handle_error_heredoc(t_shell *shell, int count)
{
	t_token	*token;
	t_list	*list;

	token = shell->tokens;
	while (!g_signal && token && count)
	{
		if (token->type == HEREDOC)
		{
			list = get_heredoc_lines(shell, token->next->line);
			shell->nbline += ft_lstsize(list);
			write_heredoc(list, token);
			ft_lstclear(&list, del_str);
			count--;
		}
		token = token->next;
	}
	dup2(shell->stdin, 0);
}
