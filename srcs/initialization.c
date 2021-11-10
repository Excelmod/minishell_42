/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:47:42 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/10 17:34:08 by adu-pavi         ###   ########.fr       */
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
	new = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (ap && ap[i] != NULL)
	{
		new[i] = ft_strdup(ap[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	init_fd_to_zero(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 2)
			shell->pipe_fd[i][j++] = 0;
		i++;
	}
}

void	initialization_shlvl(t_shell *shell)
{
	char	*str;
	int		nb;
	char	**tab;

	str = env_value(shell->env, "SHLVL");
	init_fd_to_zero(shell);
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
	if (strncmp(new, cur, ft_strlen(new)) != 0)
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
	free(tab[1]);
	tab[1] = ft_strdup("OLDPWD");
	builtin_unset(shell, tab);
	builtin_export(shell, tab);
	ft_freetabs(tab);
}

void	redisplay_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
}

void	interrupt_process(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

void	quit_process(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (core dumped)\n", 1);
}

void	signal_input(void)
{
	signal(SIGINT, redisplay_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_process(void)
{
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	initialization_shell(t_shell *shell, char **ap)
{
	shell->env = new_env(ap);
	shell->exp = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
	shell->path = ft_split(search_env(shell->env, "PATH") + 5, ':');
	shell->stdin = dup(0);
	shell->stdout = dup(1);
	signal_input();
	initialization_pwd(shell);
	initialization_shlvl(shell);
	shell->exit_status = 0;
	if (!(shell->path))
	{
		perror("shell");
		exit(0);
	}
}
