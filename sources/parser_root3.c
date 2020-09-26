/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_root3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:05:01 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 20:49:00 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Note:	Adds the new node following a precise order (left, me, right, up)
*/

void		ast_add(t_btree **ast, t_btree *add)
{
	if (add == NULL)
		return ;
	if (*ast == NULL)
		*ast = add;
	else if ((*ast)->left == NULL)
		(*ast)->left = add;
	else if ((*ast)->item == NULL)
	{
		(*ast)->item = add->item;
		ft_free((void **)&add);
	}
	else if ((*ast)->right == NULL)
		(*ast)->right = add;
	else
	{
		add->left = *ast;
		*ast = add;
	}
}
