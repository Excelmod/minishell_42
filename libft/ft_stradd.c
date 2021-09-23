/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:06:36 by ljulien           #+#    #+#             */
/*   Updated: 2021/03/13 18:29:55 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stradd(char *s, char c)
{
	char	*dest;
	int		l;

	dest = NULL;
	l = ft_strlen(s);
	dest = malloc(sizeof(*dest) * (l + 2));
	if (s != NULL && dest != NULL)
	{
		ft_strlcpy(dest, s, l + 1);
		dest[l] = c;
		dest[l + 1] = 0;
	}
	return (dest);
}
