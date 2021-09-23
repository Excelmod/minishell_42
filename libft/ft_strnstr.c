/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 20:14:14 by ljulien           #+#    #+#             */
/*   Updated: 2019/10/16 22:08:28 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *key, size_t len)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	if (key[0] == 0)
		return ((char *) src);
	while (src[i] != 0 && i < len)
	{
		n = 0;
		while (src[i + n] == key[n] && i + n < len)
		{
			if (key[n + 1] == 0)
				return ((char *)(src + i));
			n++;
		}
		i++;
	}
	return (NULL);
}
