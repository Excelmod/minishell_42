/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:19:58 by ljulien           #+#    #+#             */
/*   Updated: 2021/11/20 02:12:30 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		l1;
	int		l2;

	dest = NULL;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	dest = malloc(sizeof(*dest) * (l1 + l2 + 1));
	if (s1 != NULL && dest != NULL)
	{
		ft_strlcpy(dest, s1, l1 + 1);
	}
	if (s2 != NULL && dest != NULL)
	{
		ft_strlcpy(dest + l1, s2, l2 + 1);
	}
	return (dest);
}
