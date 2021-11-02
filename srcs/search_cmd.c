/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 00:44:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/02 19:01:26 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_cmd(t_shell *shell, char *cmd)
{
	int	i;

	i = 0;
	shell->str = ft_strdup(cmd);
	if (check_path(".", shell))
		return ;
	while (shell->path[i])
	{
		if (check_path(shell->path[i], shell))
			return ;
		i++;
	}
	if (shell->str)
		ft_putstr_fd("minishell: Permission denied: ", 2);
	else
		ft_putstr_fd("minishell: Command not found: ", 2);
	ft_putendl_fd(shell->str, 2);
	free(shell->str);
	shell->str = NULL;
}