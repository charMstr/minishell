/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:49:12 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/11 16:47:00 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note: reconnecting the previous and the following link should be done before
** calling this function
**
** note2: therefore content->next is never freed.
**
** note3: the (*del) function shoud be written specific to content
*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	if (!(lst->content == NULL))
		(*del)(lst->content);
	free(lst);
	lst = NULL;
}
