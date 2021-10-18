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

	*line = malloc(sizeof(**line));
	**line = 0;
	while (read(fd, &buf, 1) > 0)
	{
		if (buf == '\n')
			return (1);
		swap = ft_stradd(*line, buf);
		free(*line);
		*line = swap;
	}
	return (0);
}
