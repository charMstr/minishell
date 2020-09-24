/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 22:33:24 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 09:37:42 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** input:	- arg1: head of list, (ex: &head)
**			- arg2: new link to be added
**
** note2:	if *alst is NULL, it means the list was empty. new list is created
*/

void	ft_dlstadd_back(t_dlist **alst, t_dlist *new)
{
	t_dlist *tmp;

	if (!alst || !new)
		return ;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->previous = tmp;
}
