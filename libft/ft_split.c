/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:52:00 by ljulien           #+#    #+#             */
/*   Updated: 2021/08/22 01:30:39 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_tab(char const *s, char c)
{
	int		i;
	int		flag;
	int		n;

	i = 0;
	n = 0;
	flag = 1;
	while (s[i] != '\0')
	{
		if (c == s[i])
			flag = 1;
		else if (flag)
		{
			n++;
			flag = 0;
		}
		i++;
	}
	return (n);
}

static int	size_str(char const *s, char c)
{
	int		i;
	int		cut;

	i = 0;
	cut = 0;
	while (s[i] == c)
		i++;
	while (s[i] != 0 && s[i] != c)
	{
		cut++;
		i++;
	}
	return (cut);
}

static char	**ft_erasetabs(char **t, int size)
{
	size--;
	while (size >= 0)
	{
		free(t[size]);
		t[size] = NULL;
		size--;
	}
	free(t);
	t = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**t;
	int		i;
	int		ns;
	int		cut;

	ns = size_tab(s, c);
	t = malloc(sizeof(char *) * (ns + 1));
	if (!t)
		return (NULL);
	t[ns] = NULL;
	i = 0;
	while (ns--)
	{
		cut = size_str(s, c);
		t[i] = malloc(sizeof(char) * (cut + 1));
		if (!(t[i]))
			return (ft_erasetabs(t, i));
		while (*s == c)
			s++;
		ft_strlcpy(t[i++], s, cut + 1);
		s += cut;
	}
	return (t);
}
