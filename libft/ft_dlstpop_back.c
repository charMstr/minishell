/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstpop_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 22:47:50 by mli               #+#    #+#             */
/*   Updated: 2020/05/14 22:49:01 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 ** note:	this function will delete the last link of the double linked list.
 **			see ft_dlstpop_front as well.
 */

void	ft_dlstpop_back(t_dlist **head, void (*del)(void*))
{
	t_dlist **current;
	t_dlist *then;

	if (!head || !del || !*head)
		return ;
	current = head;
	while (*current)
	{

		then = (*current)->next;
		if (!then)
		{
			ft_dlstdelone(*current, del);
			*current = NULL;
			return ;
		}
		current = &(*current)->next;
	}
}
