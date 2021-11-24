/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 00:21:29 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/16 00:26:55 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare(char *in, char *out)
{
	int	i;

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
