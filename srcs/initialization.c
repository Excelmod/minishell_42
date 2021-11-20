/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:47:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/20 05:43:07 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_env(char **ap)
{
	int		i;
	char	**new;

	i = 0;
	while (ap && ap[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ap && ap[i] != NULL)
	{
		new[i] = ft_strdup(ap[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	initialization_shlvl(t_shell *shell)
{
	char	*str;
	int		nb;
	char	**tab;

	str = env_value(shell->env, "SHLVL");
	if (str)
	{
		nb = ft_atoi(str);
		if (nb < 0)
			nb = 0;
		else
			nb++;
	}
	else
		nb = 1;
	free(str);
	str = ft_itoa(nb);
	tab = malloc(sizeof(char *) * 3);
	tab[0] = ft_strdup("export");
	tab[1] = ft_strjoin("SHLVL=", str);
	tab[2] = NULL;
	builtin_export(shell, tab);
	free(str);
	tab = ft_freetabs(tab);
}

char	*check_path_pwd(char *path)
{
	char	*cur;
	char	*new;

	cur = cur_dir_name();
	if (chdir(path))
	{
		free(path);
		return (cur);
	}
	new = cur_dir_name();
	if (ft_strncmp(new, cur, ft_strlen(new)) != 0)
	{
		free(new);
		free(path);
		chdir(cur);
		return (cur);
	}
	else
	{
		free(new);
		free(cur);
		return (path);
	}
}

void	initialization_pwd(t_shell *shell)
{
	char	*str;
	char	**tab;

	str = env_value(shell->env, "PWD");
	if (str)
		str = check_path_pwd(str);
	else
		str = cur_dir_name();
	shell->pwd = str;
	tab = malloc(sizeof(char *) * 3);
	tab[0] = ft_strdup("exp");
	tab[1] = ft_strjoin("PWD=", str);
	tab[2] = NULL;
	builtin_export(shell, tab);
	ft_freetabs(tab);
}

void	initialization_shell(t_shell *shell, char **ap)
{
	shell->env = new_env(ap);
	shell->exp = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
	shell->pipes = NULL;
	shell->pid = NULL;
	shell->str = NULL;
	shell->path = NULL;
	shell->stdin = dup(0);
	shell->stdout = dup(1);
	signal_input();
	initialization_pwd(shell);
	initialization_shlvl(shell);
	shell->exit_status = 0;
}
