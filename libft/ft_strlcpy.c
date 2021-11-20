/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:13:23 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/20 02:21:22 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	n;

	n = ft_strlen(src);
	if (dstsize)
	{
		dstsize--;
		while (dstsize-- && *src != 0)
		{
			*dst = *src;
			dst++;
			src++;
		}
		*dst = 0;
	}
	return (n);
}
