/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 16:47:40 by mli               #+#    #+#             */
/*   Updated: 2020/05/25 18:01:41 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// For specifying children + special state for cmds (in, maybe, a struct)
// Ex : job argvs &

int		parser_cmd_state(t_btree *new, t_list **tklst)
{
	if (tklst_id(*tklst) == AND)
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
	if (tkid == TOKEN || tkid == D_QUOTE || tkid == S_QUOTE ||
		tkid == LESS || tkid == DLESS || tkid == GREAT || tkid == DGREAT ||
		tkid == AND)
		return (1);
	return (0);
}

int		parser_is_cmd_start(int tkid)
{
	if (tkid == -1)
		return (0);
	if (tkid == TOKEN || tkid == D_QUOTE || tkid == S_QUOTE ||
		tkid == LESS || tkid == DLESS || tkid == GREAT || tkid == DGREAT ||
		tkid == AND)
		return (1);
	return (0);
}

int		parser_cmdlst(t_list **args, t_list **tklst)
{
	t_list *tmp;

	if (!(tmp = ft_lstnew((*tklst)->content)))
		return (0);
	ft_lstadd_back(args, tmp);
	while (((*tklst) = (*tklst)->next) && parser_is_cmd_param(tklst_id(*tklst))
			&& (tmp = ft_lstnew((*tklst)->content)))
		ft_lstadd_back(args, tmp);
	if (!tmp)
	{
		ft_lstclear(args, NULL);
		return (0);
	}
	return (1);
}

int		parser_cmd(t_list **tklst, t_btree **new)
{
	if (!(*new = btree_new(NULL)))
		return (-1);
	if (!((*new)->item = lexer_init_token()))
	{
		ft_free((void **)new);
		return (-1);
	}
	((t_token *)((*new)->item))->id = LIST;
	if (!parser_cmdlst((t_list **)&((t_token *)((*new)->item))->str, tklst))
	{
		ft_free((void **)&(*new)->item);
		ft_free((void **)new);
		return (-1);
	}
	return (1);
}
