/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:48:56 by ljulien           #+#    #+#             */
/*   Updated: 2019/10/18 15:19:25 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*pnt1;
	t_list	*pnt2;

	if (!lst || !del)
		return ;
	pnt1 = *lst;
	pnt2 = pnt1;
	while (pnt1 != NULL)
	{
		pnt1 = pnt1->next;
		ft_lstdelone(pnt2, del);
		pnt2 = pnt1;
	}
	*lst = NULL;
}
