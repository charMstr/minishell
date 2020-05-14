/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 22:38:59 by mli               #+#    #+#             */
/*   Updated: 2020/05/14 22:39:28 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 ** RETURN:	pointer to very last link
 **			NULL if the head of list pointer was NULL
 */

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}
