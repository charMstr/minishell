/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 11:59:13 by mli               #+#    #+#             */
/*   Updated: 2020/05/26 12:49:45 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	btree_clear(t_btree **node, void (*del)(void *))
{
	if (!*node)
		return ;
	btree_clear(&(*node)->left, del);
	btree_clear(&(*node)->right, del);
	btree_delone(node, del);
}
