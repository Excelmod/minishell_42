/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:47:37 by ljulien           #+#    #+#             */
/*   Updated: 2019/10/16 22:08:42 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	n;

	i = 0;
	n = -1;
	while (s[i] != 0)
	{
		if (s[i] == (char)c)
			n = i;
		i++;
	}
	if (n != -1)
		return ((char *)(s + n));
	if (c == 0)
		return ((char *)(s + i));
	return (NULL);
}
