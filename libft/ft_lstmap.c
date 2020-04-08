/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 09:19:30 by mli               #+#    #+#             */
/*   Updated: 2019/10/17 22:08:59 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	iteration of (*f) on each link in order to creat a new list.
**			See ft_lstiter if you want to modify the original.
**
** note:	(*del) is passed to ft_lstclear, then to ft_lstdelone to clean the
**			whole new_list if a malloc failed in ft_lstnew.
**
** RETURN:	a new list, modified version according to (*f) function
**			NULL if original is NULL or failure in malloc.
*/

static t_list	*ft_lstfill(t_list *lst, t_list *new, void *(*f)(void *))
{
	t_list	*to_add;

	if (lst)
	{
		if (!(new = ft_lstnew(f(lst->content))))
			return (NULL);
		lst = lst->next;
	}
	if (lst)
	{
		if (!(to_add = ft_lstnew(f(lst->content))))
			return (NULL);
		new->next = to_add;
		lst = lst->next;
	}
	while (lst)
	{
		if (!(to_add->next = ft_lstnew(f(lst->content))))
			return (NULL);
		to_add = to_add->next;
		lst = lst->next;
	}
	return (new);
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;

	new = NULL;
	if ((new = ft_lstfill(lst, new, f)))
		return (new);
	ft_lstclear(&new, del);
	return (NULL);
}
