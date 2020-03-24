/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:02:31 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/15 13:02:43 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note: iteration of f function on every CONTENTS of every links of the list
**
** note2: f itself needs to deal with the case lst->content == NULL;
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!(*f))
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
