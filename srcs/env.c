/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 22:37:17 by ljulien           #+#    #+#             */
/*   Updated: 2021/09/30 00:58:00 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    builtin_env(t_shell *shell)
{
    char    **env;
    int     i;

    i = 0;
    env = shell->env;
    while (env && env[i])
    {
        ft_putendl_fd(env[i], 0);
        i++;
    }
}