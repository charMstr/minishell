/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpop_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 22:49:21 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 09:39:01 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	this function will delete the front link of the double linked list.
**			see ft_dlstpop_back as well.
*/

void	ft_dlstpop_front(t_dlist **head, void (*del)(void*))
{
	t_dlist *new_head;

	if (!head || !del || !*head)
		return ;
	new_head = (*head)->next;
	ft_dlstdelone(*head, del);
	*head = NULL;
	*head = new_head;
}
