/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 22:31:53 by mli               #+#    #+#             */
/*   Updated: 2020/05/14 22:32:32 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 ** note: next = NULL, previous = NULL, content = the argument
 ** note: if content is NULL it doesnt mather it is still created as is.
 **
 ** RETURN:	new link that was malloced
 **			NULL pointer if failure
 */

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist *new;

	if (!(new = (t_dlist *)malloc(sizeof(*new))))
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}
