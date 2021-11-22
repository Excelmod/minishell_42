/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 22:09:15 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/18 23:33:04 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_line(int fd, char **line)
{
	static char	buf;
	char		*swap;
	int			r;

	*line = malloc(sizeof(**line));
	**line = 0;
	r = read(fd, &buf, 1);
	if (r == 0)
		return (0);
	while (1)
	{
		if (r)
		{
			if (buf == '\n')
				return (1);
			swap = ft_stradd(*line, buf);
			free(*line);
			*line = swap;
		}
		r = read(fd, &buf, 1);
	}
	return (0);
}
