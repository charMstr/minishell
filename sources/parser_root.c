/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_root.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:05:01 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 20:49:17 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Note:	Create the id of the new ast made from a subshell as a subshell
**
** RETURN:	1 : Succeed
**			-1 : Allocation failure
*/

int			parser_be_subshell(t_btree **new)
{
	t_btree *tmp;
	t_token *token;

	tmp = NULL;
	if (!(token = ft_memalloc(sizeof(t_token))))
		return (-1);
	token->id = SUBSHELL;
	if ((*new)->item != NULL)
	{
		if (!(tmp = btree_new(token)))
		{
			ft_free((void **)&token);
			return (-1);
		}
		tmp->left = *new;
		*new = tmp;
	}
	else
		(*new)->item = token;
	return (1);
}

/*
** Note:	Returns the new child by filling *new
**
** Cases:
**		- It is a cmd, a linked list is created and directly added
**		- It is the begin of a subshell, as in handle-semi, it re-creates an AST
**		- Else : parse just one token
**
** Note:	Since the AST is created in dlst->next->content, returning NULL will
**			notify a problem and won't cause any leak
** RETURN:	1 : Succeed
**			0 : tklst has no more tokens
**			-1 : Allocation failure
*/

int			parser_next_child(t_dlist **dlst, t_list **tklst, t_btree **new)
{
	if (parser_is_cmd_start(tklst_id(*tklst)))
		return (parser_cmd(tklst, new));
	if (parser_do_subtree(token_id((*tklst)->content)))
	{
		*tklst = (*tklst)->next;
		if (!*tklst)
			return (0);
		if (!((*dlst)->next = ft_dlstnew(NULL)))
			return (-1);
		(*dlst)->next->previous = *dlst;
		if (!(*new = parser_create_ast((*dlst)->next, tklst)))
			return (-1);
		if (parser_be_subshell(new) == -1)
			return (-1);
		ft_free((void **)&((*dlst)->next));
	}
	else
	{
		if (!(*new = btree_new((*tklst)->content)))
			return (-1);
	}
	if (*tklst)
		*tklst = (*tklst)->next;
	return (1);
}

/*
** Note:	As it is called, this function will handle the semi (;) case
**			It will do smthing only if the next token is a cmd, not ) or empty
**
** Note:	Re-create an AST with dlst->next + the remaining tokens
**			and add the returned AST as a child of the `;' just parsed
**
** RETURN:	1 : Succeed
**			0 : The conditions aren't good
**			-1 : Allocation failure
*/

int			parser_handle_semi(t_dlist **dlst, t_list **tklst)
{
	t_btree		*new;

	if (!(*tklst && token_id((*tklst)->content) == SEMI &&
		(tklst_id((*tklst)->next) != RBRACE) && (*tklst = (*tklst)->next)))
		return (0);
	if (!((*dlst)->next = ft_dlstnew(NULL)))
		return (-1);
	(*dlst)->next->previous = *dlst;
	if (!(new = parser_create_ast((*dlst)->next, tklst)))
		return (-1);
	ft_free((void **)&((*dlst)->next));
	ast_add((t_btree **)&(*dlst)->content, new);
	return (1);
}

/*
** Input:	A link from a dlst where the new AST have to be built
**			The address of the token list to be parsed (so we can move forward
**			through functions)
**
** Note:	Main function of creation of an AST
**
** RETURN:	A btree (AST) which item are (t_token *)
**			NULL if a malloc failed.
** Note:	Since the AST is created in dlst->content, returning NULL will
**			notify a problem and won't cause any leak
**			(if dlst is cleared properly)
*/

t_btree		*parser_create_ast(t_dlist *dlst, t_list **tklst)
{
	t_btree		*new;
	int			state;

	if (!(dlst->content = btree_new(NULL)))
		return (NULL);
	while (*tklst && token_id((*tklst)->content) != RBRACE)
	{
		if ((state = parser_next_child(&dlst, tklst, &new)) == 1)
			ast_add((t_btree **)&dlst->content, new);
		else if (state == -1)
			return (NULL);
		else if (parser_handle_semi(&dlst, tklst) == -1)
			return (NULL);
	}
	return (dlst->content);
}

t_btree		*parser_root(t_list *tklst, t_control *control)
{
	t_dlist		*dlst;
	t_btree		*ast;
	t_list		*tkcpy;

	ast = NULL;
	if (!(tkcpy = tklst))
		return (NULL);
	if ((dlst = ft_memalloc(sizeof(*dlst))) &&
		(ast = parser_create_ast(dlst, &tkcpy)))
	{
		ft_lstremove_if(&tklst, NULL, tkcmp_braces, del_token);
		ft_lstclear(&tklst, NULL);
		ft_dlstclear(&dlst, NULL);
		parser_pipe_priority(&ast);
	}
	else
	{
		control->quit = 1;
		ft_lstclear(&tklst, del_token);
		ft_dlstclearback_addr(&dlst, (void (*)(void **))&del_ast);
	}
	return (ast);
}
