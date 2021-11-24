/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 02:04:24 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/20 00:55:15 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_numeric_value(char *str)
{
	int	status;
	int	sign;

	status = 0;
	sign = 0;
	if (*str == '+' && str++)
		sign = 0;
	else if (*str == '-' && str++)
		sign = 1;
	while (*str)
	{
		if (*str < '0' || *str > '9')
		{
			ft_putendl_fd("bash: exit: numeric argument required", 2);
			return (2);
		}
		status *= 10;
		status += *str - '0';
		str++;
	}
	if (sign)
		status *= -1;
	return (status % 256);
}

int	exit_pipe(t_shell *shell, char **av)
{
	int	status;

	status = 0;
	if (av[1] == NULL)
		status = shell->exit_status;
	else if (av[1] && av[2])
	{
		ft_putendl_fd("bash: exit: too many arguments", 2);
		return (1);
	}
	else if (av[1] && av[2] == NULL)
	{
		status = check_exit_numeric_value(av[1]);
	}
	exit_free(shell, status);
	return (status);
}

int	exit_shell(t_shell *shell, char **av)
{
	int	status;

	status = 0;
	if (av[1] == NULL)
		status = shell->exit_status;
	else if (av[2])
	{
		ft_putendl_fd("bash: exit: too many arguments", 2);
		return (1);
	}
	else if (av[2] == NULL)
	{
		status = check_exit_numeric_value(av[1]);
	}
	ft_putendl_fd("exit", 2);
	exit_free(shell, status);
	return (status);
}
