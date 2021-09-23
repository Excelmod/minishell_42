/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:01:23 by ljulien           #+#    #+#             */
/*   Updated: 2019/10/16 22:07:06 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	lgh;

	dest = NULL;
	lgh = ft_strlen(src);
	dest = malloc(sizeof(*dest) * (lgh + 1));
	if (dest)
		ft_strlcpy(dest, src, lgh + 1);
	return (dest);
}
