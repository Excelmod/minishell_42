/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:55:36 by ljulien           #+#    #+#             */
/*   Updated: 2019/10/16 21:35:32 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	s = src;
	d = dst;
	if (dst > src)
		while (n--)
			d[n] = s[n];
	else if (dst < src)
		while (n--)
			*d++ = *s++;
	return (dst);
}
