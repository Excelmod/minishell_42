/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 20:03:13 by ljulien           #+#    #+#             */
/*   Updated: 2019/10/16 22:04:25 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lgh(int n)
{
	int		lgh;

	lgh = 1;
	if (n < 0)
		lgh++;
	while (n / 10)
	{
		n = n / 10;
		lgh++;
	}
	return (lgh);
}

static void	ft_fills(int n, int lgh, char *s)
{
	int		stop;

	stop = 0;
	s[lgh--] = 0;
	if (n < 0)
	{
		s[0] = '-';
		stop = 1;
		s[lgh--] = -(n % 10) + '0';
		n /= 10;
		n *= -1;
	}
	while (lgh >= stop)
	{
		s[lgh--] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*s;
	int		lgh;

	lgh = ft_lgh(n);
	s = malloc((lgh + 1) * sizeof(char));
	if (s != NULL)
		ft_fills(n, lgh, s);
	return (s);
}
