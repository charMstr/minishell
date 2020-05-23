/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 16:47:40 by mli               #+#    #+#             */
/*   Updated: 2020/05/23 23:23:29 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// For specifying children + special state for cmds (in, maybe, a struct)
// Ex : job argvs &

int		parser_is_cmd_state(int tkid)
{
	if (tkid == -1)
		return (0);
	if (tkid == AND)
		return (1);
	return (0);
}

int			parser_cmd_state(t_btree *new, t_list **tklst)
{
	if ((*tklst) && parser_is_cmd_state(token_id((*tklst)->content)))
	{
		if (!(new->right = btree_new((*tklst)->content)))
			return (0);
		(*tklst) = (*tklst)->next;
	}
	return (1);
}

int		parser_is_cmd_param(int tkid)
{
	if (tkid == -1)
		return (0);
	if (tkid == TOKEN || tkid == D_QUOTE || tkid == S_QUOTE)
		return (1);
	return (0);
}

int			parser_cmd(t_list **tklst, t_btree *new)
{
	t_list *args;
	t_list *tmp;

	args = NULL;
	if (!(token_id((*tklst)->content) == TOKEN && (*tklst)->next &&
				parser_is_cmd_param(token_id((*tklst)->next->content))))
		return (0);
	if (!(new->left = btree_new(NULL)))
		return (-1);
	(*tklst) = (*tklst)->next;
	while ((*tklst) && parser_is_cmd_param(token_id((*tklst)->content)))
	{
		if (!(tmp = ft_lstnew((*tklst)->content)))
			break ;
		ft_lstadd_back(&args, tmp);
		(*tklst) = (*tklst)->next;
	}
	if ((*tklst && parser_is_cmd_param(token_id((*tklst)->content))) ||
			parser_cmd_state(new, tklst) == 0)
	{
		ft_lstclear(&args, NULL);
		return (-1);
	}
	new->left->item = args;
	return (1);
}
