/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 23:42:20 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 09:36:06 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_add(t_btree **root, t_btree *new, int (*cmpf)(void *, void *))
{
	t_btree *parent;
	t_btree *node;
	int		side;

	if (!root || !new)
		return ;
	if (!(node = *root))
		*root = new;
	while (node)
	{
		parent = node;
		if ((side = cmpf(node->item, new->item)) < 0)
			node = node->right;
		else
			node = node->left;
	}
	if (side >= 0)
		parent->left = new;
	else
		parent->right = new;
}
