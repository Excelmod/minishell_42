/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:25:40 by lchristo          #+#    #+#             */
/*   Updated: 2021/10/05 16:25:43 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     compare(char *in, char *out)
{
    int i;

    i = 0;
    if (in == NULL || out == NULL)
        return (0);
    if (ft_strlen(in) != ft_strlen(out))
        return (0);
    while (in[i] == out[i] && in[i] != '\0')
    {
        i++;
    }
    if (in[i] == '\0' && out[i] == '\0')
        return (1);
    return (0);
}