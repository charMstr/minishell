/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstfirst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 22:40:27 by mli               #+#    #+#             */
/*   Updated: 2020/05/14 22:40:48 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 ** RETURN:	pointer to very first link
 **			NULL if the head of list pointer was NULL
 */

t_dlist	*ft_dlstfirst(t_dlist *lst)
{
	if (lst)
		while (lst->previous)
			lst = lst->previous;
	return (lst);
}
