/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 23:16:41 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/20 05:45:32 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_cd(t_shell *shell, char **arg)
{
	char	*path;
	char	*tmp;

	tmp = env_value(shell->env, "HOME");
	if (arg[1][0] == '/')
		path = ft_strdup(arg[1]);
	else if (arg[1][0] == '~' && (arg[1][1] == '/' || arg[1][1] == 0)
			&& search_env(shell->env, "HOME"))
		path = path_join(tmp, arg[1] + 1);
	else if (arg[1][0] == '-' && arg[1][1] == 0)
	{
		path = env_value(shell->env, "OLDPWD");
	}
	else
	{
		free(tmp);
		tmp = ft_strjoin(shell->pwd, "/");
		path = ft_strjoin(tmp, arg[1]);
	}
	free(tmp);
	return (path);
}

int	handle_error_cd(t_shell *shell, char **arg)
{
	char	*str;

	str = NULL;
	if (arg[1] && arg[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if (arg[1] && arg[1][0] == '-' && arg[1][1] == 0)
	{
		str = env_value(shell->env, "OLDPWD");
		if (str == NULL)
		{
			free(str);
			ft_putendl_fd("minishell: cd: 'OLDPWD' not define", 2);
			return (1);
		}
	}
	free(str);
	return (0);
}

int	builtin_cd(t_shell *shell, char **arg)
{
	char	*path;

	if (arg && (arg[1] || search_env(shell->env, "HOME")))
	{
		if (handle_error_cd(shell, arg))
			return (1);
		if (arg[1])
			path = path_cd(shell, arg);
		else
			path = env_value(shell->env, "HOME");
		if (chdir(path))
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(path);
			free(path);
			return (errno);
		}
		else
		{
			if (arg[1] && arg[1][0] == '-' && arg[1][1] == 0)
				ft_putendl_fd(path, 1);
			change_pwd(shell, path);
		}
	}
	return (0);
}
