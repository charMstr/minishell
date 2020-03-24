/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 20:16:44 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/13 17:04:42 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** usage: head = ft_lstrev(head);
**
** note: on the first run, previous is NULL therefore, lst->next = NULL, the
** first element becomes the very last one.
**
** RETURN: the linked list itself is turned upside down, not a copy.
*/

t_list	*ft_lstrev(t_list *lst)
{
	t_list *tmp;
	t_list *previous;

	if (!lst)
		return (NULL);
	previous = NULL;
	while (lst != NULL)
	{
		tmp = lst->next;
		lst->next = previous;
		previous = lst;
		lst = tmp;
	}
	return (previous);
}
