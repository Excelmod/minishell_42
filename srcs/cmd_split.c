/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 21:07:08 by ljulien           #+#    #+#             */
/*   Updated: 2021/04/22 12:47:31 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	    	size_tab(int *s, int c)
{
	int		i;
	int		flag;
	int		n;

	i = 0;
	n = 0;
	flag = 1;
	while (s[i] != 0)
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

int	    	size_str(int *s, int c)
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

int		**ft_erasetabs(int **t, int size)
{
	size--;
	while (size)
	{
		free(t[size]);
		t[size] = NULL;
	}
	free(t);
	t = NULL;
	return (NULL);
}

void		    ft_strlcpy_int(int *dst, int *src, size_t dstsize)
{
	if (dstsize)
	{
		dstsize--;
		while (dstsize-- && *src != 0)
        {
			*dst = *src;
            dst += sizeof(*dst);
            src += sizeof(*src);
        }
		*dst = 0;
	}
}

int		    	**ft_split_int(int *s, int c)
{
	int	**t;
	int		i;
	int		ns;
	int		cut;

	ns = size_tab(s, c);
	if (!(t = malloc(sizeof(s) * (ns + 1))))
		return (NULL);
    
	t[ns] = NULL;
	i = 0;
    while (ns--)
	{
		cut = size_str(s, c);
		if (!(t[i] = malloc(sizeof(*s) * (cut + 1))))
			return (ft_erasetabs(t, i));
		/*while (*s == c)
			s += 2;
		ft_strlcpy_int(t[i], s, cut + 1);
        i++;
		s += cut * 2;*/
	}
	return (t);
}