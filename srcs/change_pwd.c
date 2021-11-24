/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 05:26:52 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/20 05:28:45 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cutstr(char *str, char sep, int i)
{
	char	*tmp;
	int		cnt;

	cnt = 0;
	str = str + i;
	tmp = str + 1;
	while (i && *str != sep)
	{
		i--;
		str--;
	}
	while (tmp[cnt])
		cnt++;
	ft_memmove(str, tmp, cnt + 1);
	return (i);
}

void	update_pwd_env(t_shell *shell, char *path)
{
	char	**tab;

	tab = malloc(sizeof(char *) * 3);
	tab[0] = ft_strdup("export");
	tab[2] = NULL;
	tab[1] = ft_strjoin("OLDPWD=", shell->pwd);
	builtin_export(shell, tab);
	free(tab[1]);
	tab[1] = NULL;
	free(shell->pwd);
	shell->pwd = NULL;
	shell->pwd = path;
	tab[1] = ft_strjoin("PWD=", path);
	builtin_export(shell, tab);
	ft_freetabs(tab);
}

void	change_pwd(t_shell *shell, char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '.' && (path[i - 1] == '/' || i == 0)
			&& (!path[i + 1] || ft_isset("/.", path[i + 1])))
		{
			i = ft_cutstr(path, '/', i);
			if (path[i] == '.')
				i = ft_cutstr(path, '/', i);
			if (*path == 0)
			{
				path[0] = '/';
				path[1] = 0;
				i = 1;
			}
		}
		else if (path[i] == '/' && ((path[i + 1] == 0 && i)
				|| path[i + 1] == '/'))
			ft_memmove(path + i, path + i + 1, ft_strlen(path + i + 1) + 1);
		else
			i++;
	}
	update_pwd_env(shell, path);
}
