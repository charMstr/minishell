/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 09:18:11 by mli               #+#    #+#             */
/*   Updated: 2019/10/16 15:04:43 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	deletes element and all following ones: different from ft_lstdelone
**
** note:	if you want to delete from the middle of the list:
**			-	it puts the pointer to NULL so it ends the list here.
**			-	1st arg: &(previous->next) should be used to NULLify the
**				correct pointer.
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*then;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		then = current->next;
		ft_lstdelone(current, del);
		current = then;
	}
	*lst = NULL;
}
