/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:21:37 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 20:30:03 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			token_id(t_token *token)
{
	if (!token)
		return (-1);
	return (token->id);
}

int			tklst_id(t_list *tklst)
{
	if (!tklst)
		return (-1);
	return (token_id(tklst->content));
}

int			btree_id(t_btree *node)
{
	if (!node)
		return (-1);
	return (token_id(node->item));
}
