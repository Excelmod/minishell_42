/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 00:44:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/23 19:16:31 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_cmd(t_shell *shell, char *cmd)
{
	int	i;

	i = 0;
	shell->cmd = NULL;
	if (check_path(shell, ".", cmd))
		return ;
	if (check_path(shell, "/bin", cmd))
		return ;
	while (shell->path[i])
	{
		if (check_path(shell, shell->path[i], cmd))
			return ;
		i++;
	}
	if (shell->cmd)
		ft_putstr_fd("minishell: Permission denied: ", 2);
	else
		ft_putstr_fd("minishell: Command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	free(shell->cmd);
	shell->cmd = NULL;
}