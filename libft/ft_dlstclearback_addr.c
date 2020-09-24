/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclearback_addr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 09:18:11 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 09:38:39 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	Deletes from the end and giving the address of
**			the element being erased
*/

void	ft_dlstclearback_addr(t_dlist **lst, void (*del)(void **))
{
	t_dlist	*then;

	if (!lst || !*lst)
		return ;
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	while (*lst)
	{
		then = (*lst)->previous;
		if (del)
			del(&(*lst)->content);
		ft_free((void **)lst);
		(*lst) = then;
	}
}
