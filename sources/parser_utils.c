/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:21:37 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 11:21:52 by mli              ###   ########.fr       */
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

void		parser_disp(t_token *node, t_btree *parent)
{
	int		i;
	int		fd;
	char	*str;

	fd = 1;
	if (token_id(node) == LIST)
		str = (char	[5]){'l', 's', 't', 47 \
			+ ft_lstsize((t_list *)node->str), '\0'};
	else if (token_id(node) == SUBSHELL)
		str = "shell";
	else
		str = (node ? node->str : "null");
	i = -1;
	ft_putstr_fd("[", fd);
	while (++i < SIZE_LEAF - 2 && str[i])
		ft_putchar_fd(str[i], fd);
	while (i++ < SIZE_LEAF - 2)
		ft_putchar_fd(' ', fd);
	ft_putstr_fd("]", fd);
	(void)parent;
}
