/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:35:11 by ljulien           #+#    #+#             */
/*   Updated: 2019/10/16 22:07:17 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	n;
	size_t	lgh;

	lgh = ft_strlen(src);
	n = 0;
	while (dst[n] && n < dstsize)
		n++;
	lgh += n;
	if (n + 1 < dstsize)
	{
		dstsize -= n + 1;
		dst += n;
		while (dstsize-- && *src != 0)
			*dst++ = *src++;
		*dst = 0;
	}
	return (lgh);
}
