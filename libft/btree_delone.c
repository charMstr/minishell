/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_delone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 11:59:13 by mli               #+#    #+#             */
/*   Updated: 2020/05/26 12:50:58 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"
#include "libft.h"

void	btree_delone(t_btree **node, void (*del)(void *))
{
	if (!*node)
		return ;
	if (del)
		del((*node)->item);
	ft_free((void **)node);
}
