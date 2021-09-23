/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:44:27 by ljulien           #+#    #+#             */
/*   Updated: 2019/10/16 22:12:00 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*news;
	int		i;

	i = 0;
	news = NULL;
	news = malloc(sizeof(*s) * (ft_strlen(s) + 1));
	if (news != NULL && s != NULL)
	{
		while (s[i] != 0)
		{
			news[i] = f(i, s[i]);
			i++;
		}
		news[i] = 0;
	}
	return (news);
}
