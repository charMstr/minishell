/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_root2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:05:01 by mli               #+#    #+#             */
/*   Updated: 2020/09/28 10:46:00 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		del_ast(t_btree **node)
{
	btree_clear(node, NULL);
}

int			parser_do_subtree(int tkid)
{
	if (tkid == LBRACE)
		return (1);
	return (0);
}

int			tkcmp_braces(t_token *token)
{
	int id;

	id = token_id(token);
	if (id == LBRACE || id == RBRACE)
		return (0);
	return (1);
}

/*
** Input:	The token list from the lexing part.
**
** Note:	This func is the root func for the parsing.
**			It will clean the token list in either case, success or fail
**			dlst linked list will contain one AST
**			(or more if the problem happened inside a recursion)
** Note:	If a malloc failed, the dlst is removed from the last link to the
**			first, because all sub-ast should be linked but we have to avoid
**			double free (or maybe they are not and it is useless)
**
** note:	the call to parser_LIST_to_CMD_root will reparcour the tree and
**			transform the nodes of type LIST, into nodes of type CMD, creating
**			a structure containing argv and a linked list for redirections.
**			(control->quit raised inside the subfunction if failure).
** RETURN:	A btree (AST) which item are (t_token *)
**			NULL if a malloc failed.
*/

void		parser_btree_reverse_pipe(t_btree **ast)
{
	int		id;
	t_btree	*lchild;

	lchild = (*ast)->left;
	while (btree_id(lchild) == PIPE)
		lchild = lchild->left;
	if ((id = btree_id(lchild)) == -1)
		return ;
	if (id == LIST || id == SUBSHELL)
		return ;
	(*ast)->left = lchild->right;
	lchild->right = *ast;
	*ast = lchild;
}

void		parser_pipe_priority(t_btree **ast)
{
	if (!ast || !*ast)
		return ;
	parser_pipe_priority(&(*ast)->left);
	parser_pipe_priority(&(*ast)->right);
	if (btree_id(*ast) == PIPE)
		parser_btree_reverse_pipe(ast);
}
