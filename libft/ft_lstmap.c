/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:46:31 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/15 00:31:08 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note: iteration of (*f) on each link. see ft_lstiter if no copy wanted.
**
** note2: (*del) is passed to ft_lstclear to clean the whole new_list if a
** malloc failed in ft_lstnew.
**
** RETURN: copy of lst which is modified according to (*f) function. The RETURN
** can be NULL if lst is NULL or if failure mallocing midway
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_list;
	t_list *new_link;

	new_list = NULL;
	while (lst)
	{
		if (*f)
			new_link = ft_lstnew((*f)(lst->content));
		if (!new_link && (*del))
		{
			ft_lstclear(&new_list, (*del));
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_link);
		lst = lst->next;
	}
	return (new_list);
}
