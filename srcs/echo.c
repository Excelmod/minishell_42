/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 00:55:27 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/03 18:47:15 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     builtin_echo(char **args)
{
    int i;
    int option;

    i = 1;
    option = 0;
    if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
    {
        option = 1;
        i++;
    }
    while(args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (option == 0)
        ft_putstr_fd("\n", 1);
    return(0);
}