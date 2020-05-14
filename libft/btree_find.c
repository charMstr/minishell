/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 14:24:47 by mli               #+#    #+#             */
/*   Updated: 2020/05/14 23:59:30 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*btree_find(t_btree *root, void *data_ref, int (*cmpf)(void *, void *))
{
	void	*res;

	if (!root)
		return (NULL);
	if ((res = btree_find(root->left, data_ref, cmpf)))
		return (res);
	if (!cmpf(root->item, data_ref))
		return (root->item);
	if ((res = btree_find(root->right, data_ref, cmpf)))
		return (res);
	return (NULL);
}
