/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:21:44 by ljulien           #+#    #+#             */
/*   Updated: 2019/10/21 23:03:41 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*pnt;

	if (*alst && alst && new)
	{
		pnt = ft_lstlast(*alst);
		pnt->next = new;
	}
	else if (!*alst && alst && new)
	{
		*alst = new;
		(*alst)->next = NULL;
	}
}
