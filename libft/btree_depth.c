/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_depth.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 14:56:35 by mli               #+#    #+#             */
/*   Updated: 2020/05/14 23:59:25 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		btree_depth(t_btree *root)
{
	int	max[3];

	if (!root)
		return (0);
	max[0] = btree_depth(root->left);
	max[1] = btree_depth(root->right);
	max[2] = (max[0] > max[1] ? max[0] : max[1]);
	return (max[2] + 1);
}
