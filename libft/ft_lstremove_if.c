/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 11:44:18 by mli               #+#    #+#             */
/*   Updated: 2020/05/26 11:51:12 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove_if(t_list **begin_list, void *data_ref, int (*cmp)(),
		void (*free_fct)(void *))
{
	t_list	*current;
	t_list	*to_delete;

	while (*begin_list && !((*cmp)((*begin_list)->content, data_ref)))
	{
		to_delete = *begin_list;
		*begin_list = to_delete->next;
		ft_lstdelone(to_delete, free_fct);
	}
	current = *begin_list;
	while (current != NULL)
	{
		if (current->next && !((*cmp)(current->next->content, data_ref)))
		{
			to_delete = current->next;
			current->next = current->next->next;
			ft_lstdelone(to_delete, free_fct);
		}
		else
			current = current->next;
	}
}
