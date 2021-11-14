/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 00:44:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/14 16:49:34 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_cmd(t_shell *shell, t_cmd *cmd, char *cmd_name)
{
	int	i;

	i = 0;
	cmd->str = ft_strdup(cmd_name);
	if (check_path(".", cmd))
		return ;
	while (shell->path[i])
	{
		if (check_path(shell->path[i], cmd))
			return ;
		i++;
	}
	if (cmd->str)
		ft_putstr_fd("minishell: Permission denied: ", 2);
	else
		ft_putstr_fd("minishell: Command not found: ", 2);
	ft_putendl_fd(cmd->str, 2);
	free(cmd->str);
	cmd->str = NULL;
}