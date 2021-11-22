/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 00:44:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/22 12:48:22 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	message_error_minishell(char *cmd, char *error)
{
	ft_putstr_fd("minishell", 2);
	if (cmd)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(cmd, 2);
	}
	if (error)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(error, 2);
	}
	ft_putstr_fd("\n", 2);
}

int	search_cmd(t_shell *shell, char *cmd, char **path_cmd)
{
	int	i;

	i = 0;
	*path_cmd = NULL;
	if (ft_strrchr(cmd, '/') != NULL && check_path(NULL, cmd, path_cmd))
		return (1);
	else if (ft_strrchr(cmd, '/') == NULL)
	{
		while (shell->path && shell->path[i])
		{
			if (check_path(shell->path[i], cmd, path_cmd))
				return (1);
			i++;
		}
	}
	if (*path_cmd)
	{
		message_error_minishell(cmd, "Permission denied");
		return (126);
	}	
	else
		message_error_minishell(cmd, "Command not found");
	return (127);
}
