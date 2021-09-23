/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:13:01 by ljulien           #+#    #+#             */
/*   Updated: 2019/10/16 22:10:00 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lgh(int nb)
{
	int	lgh;

	lgh = 1;
	while (nb / 10)
	{
		nb = nb / 10;
		lgh = 10 * lgh;
	}
	return (lgh);
}

static void	ft_wnub(int nb, int lgh, int fd)
{
	char	num;
	int		c;

	c = nb;
	while (lgh)
	{
		nb = c / lgh;
		c = c - (nb * lgh);
		lgh = lgh / 10;
		num = nb + '0';
		write(fd, &num, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	num;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
	{
		if (n < 0)
		{
			num = '-';
			write(fd, &num, 1);
			n *= -1;
		}
		ft_wnub(n, ft_lgh(n), fd);
	}
}
