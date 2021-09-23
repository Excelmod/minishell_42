/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:06:17 by ljulien           #+#    #+#             */
/*   Updated: 2019/10/21 22:59:35 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*point;
	size_t	i;

	i = 0;
	point = NULL;
	point = malloc(count * size);
	if (point == NULL)
		return (point);
	while (i < count * size)
		point[i++] = 0;
	return (point);
}
