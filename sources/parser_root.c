#include "minishell.h"

void		del_ast(t_btree **node)
{
	btree_clear(node, NULL);
}

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

int			parser_do_subtree(int tkid)
{
	if (tkid == LBRACE)
		return (1);
	return (0);
}

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

int		parser_next_child(t_dlist **dlst, t_list **tklst, t_btree **new)
{
//	printf("ENTER WITH : [%d]\t'%s'\n",
//		token_id((*tklst)->content), ((t_token *)(*tklst)->content)->str);

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
//	printf("\nNEW CONTAINS\n");
//		btree_debug(*new, parser_disp);
	}
	else
	{
		if (!(*new = btree_new((*tklst)->content)))
			return (-1);
	}
	if (*tklst)
		*tklst = (*tklst)->next;
//	if ((*new)->item)
//		printf("New is : [%d]\t'%s'\n", token_id((*new)->item), ((t_token *)(*new)->item)->str);
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
//		printf("%d\n", token_id(tklst->content));
		if ((state = parser_next_child(&dlst, tklst, &new)) == 1)
			ast_add((t_btree **)&dlst->content, new);
		else if (state == -1)
			return (NULL);
		else if (parser_handle_semi(&dlst, tklst) == -1)
			return (NULL);
	}
	return (dlst->content);
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

t_btree		*parser_root(t_list *tklst, t_control *control)
{
	t_dlist		*dlst;
	t_btree		*ast;
	t_list		*tkcpy;

	ast = NULL;
	if (!(tkcpy = tklst))
		return (NULL);
//	debug_tokens_list(tklst);
	if ((dlst = ft_memalloc(sizeof(*dlst))) &&
		(ast = parser_create_ast(dlst, &tkcpy)))
	{
		btree_debug(ast, parser_disp);
		ft_lstremove_if(&tklst, NULL, tkcmp_braces, del_token);
		ft_lstclear(&tklst, NULL);
		ft_dlstclear(&dlst, NULL);
	}
	else
	{
		printf("AST FAILED\n");
		control->quit = 1;
		ft_lstclear(&tklst, del_token);
		ft_dlstclearback_addr(&dlst, (void (*)(void **))&del_ast);
	}
//	parser_LIST_to_CMD_root(ast, control);
	return (ast);
}
