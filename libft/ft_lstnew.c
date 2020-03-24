/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 17:50:59 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/10 18:32:53 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note: next = NULL, content = the argument
** note2: if content is NULL it doesnt mather it is still created as is.
**
** RETURN: new link that was malloced, or NULL pointer if malloc failed.
*/

t_list	*ft_lstnew(void *content)
{
	t_list *ptr_new_link;

	if (!(ptr_new_link = malloc(sizeof(t_list))))
		return (NULL);
	ptr_new_link->content = content;
	ptr_new_link->next = NULL;
	return (ptr_new_link);
}
