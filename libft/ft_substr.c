/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:27:21 by ljulien           #+#    #+#             */
/*   Updated: 2019/10/18 17:20:05 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	n;

	sub = NULL;
	n = 0;
	sub = malloc(sizeof(char) * (len + 1));
	if (ft_strlen(s) < (size_t)start)
	{
		*sub = 0;
		return (sub);
	}
	if (s != NULL && sub != NULL)
	{
		s += start;
		while (n < len && s[n])
		{
			sub[n] = s[n];
			n++;
		}
		sub[n] = 0;
	}
	return (sub);
}
