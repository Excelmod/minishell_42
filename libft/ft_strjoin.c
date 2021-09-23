/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:19:58 by ljulien           #+#    #+#             */
/*   Updated: 2021/02/08 22:27:15 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i = i + 1;
	}
	return (i);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	n;

	n = ft_strlen(src);
	if (dstsize)
		dstsize--;
	while (dstsize-- && *src != 0)
		*dst++ = *src++;
	*dst = 0;
	return (n);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		l1;
	int		l2;

	dest = NULL;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	dest = malloc(sizeof(*dest) * (l1 + l2 + 1));
	if (s1 != NULL && s2 != NULL && dest != NULL)
	{
		ft_strlcpy(dest, s1, l1 + 1);
		ft_strlcpy(dest + l1, s2, l2 + 1);
	}
	return (dest);
}
