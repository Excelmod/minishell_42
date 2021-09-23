/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:41:41 by ljulien           #+#    #+#             */
/*   Updated: 2021/04/14 15:22:54 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	cut[2];
	size_t	l1;
	char	*strim;

	l1 = ft_strlen(s1);
	cut[0] = 0;
	cut[1] = l1 - 1;
	while (ft_isset(set, s1[cut[0]]) && s1[cut[0]])
		cut[0]++;
	while (s1[cut[0]] && ft_isset(set, s1[cut[1]]) && cut[0] < cut[1])
		cut[1]--;
	strim = NULL;
	strim = malloc(sizeof(char) * (cut[1] - cut[0] + 2));
	if (strim)
		ft_strlcpy(strim, s1 + cut[0], (cut[1] - cut[0]) + 2);
	return (strim);
}
