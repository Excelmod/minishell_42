/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 00:44:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/20 04:01:56 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_cmd(t_shell *shell, char *cmd, char **path_cmd)
{
	int	i;

	i = 0;
	*path_cmd = NULL;
	if (check_path(NULL, cmd, path_cmd))
		return (1);
	while (shell->path && shell->path[i])
	{
		if (check_path(shell->path[i], cmd, path_cmd))
			return (1);
		i++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (*path_cmd)
	{
		ft_putendl_fd(" : Permission denied", 2);
		return (126);
	}	
	else
		ft_putendl_fd(" : Command not found", 2);
	return (127);
}
