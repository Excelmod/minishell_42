/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:28:17 by user42            #+#    #+#             */
/*   Updated: 2021/09/27 21:05:19 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_env(char **env, char *search)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(search);
	while (env[i] != NULL)
	{
		if ((ft_strncmp(env[i], search, l) == 0) && env[i][l] == '=')
			return (env[i]);
		i++;
	}
	return (0);
}

char	*env_value(char **env, char *search)
{
	int i;
	char *l;
	char *str;
	
	i = 0;
	l = search_env(env, search);
	while (l && l[i] != '=')
		i++;
	if (l)
		str = ft_strdup(l + i + 1);
	else
		str = NULL;
	return (str);
}

char	*path_join(char *s1, char *s2)
{
	char	*path;
	char	*tmp;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	free(tmp);
	return (path);
}

int	check_path(t_shell *shell, char *path, char *cmd)
{
	char	*str;

	str = path_join(path, cmd);
	if (access(str, F_OK) == 0)
	{
		free(shell->cmd);
		shell->cmd = ft_strdup(str);
		if (access(str, X_OK) == 0)
		{
			free(str);
			return (1);
		}
	}
	free(str);
	return (0);
}
