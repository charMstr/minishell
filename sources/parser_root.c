#include "minishell.h"

void		del_ast(t_btree **node)
{
	btree_clear(node, NULL);
}

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

// Filling New with the new child
// Return -1 if allocation pb,
// 0 if tklst has no more tokens
// 1 on success
int		parser_next_child(t_dlist **dlst, t_list **tklst, t_btree **new)
{
//	printf("ENTER WITH : [%d]\t'%s'\n",
//		token_id((*tklst)->content), ((t_token *)(*tklst)->content)->str);

	if (parser_is_cmd_start(tklst_id(*tklst)))
		return (parser_cmd(tklst, new));
	if (!parser_do_subtree(token_id((*tklst)->content)))
	{
		if (!(*new = btree_new((*tklst)->content)))
			return (-1);
	}
	else
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

//		debug_tokens_list(*tklst);
	}
	if (*tklst)
		*tklst = (*tklst)->next;
//	if ((*new)->item)
//		printf("New is : [%d]\t'%s'\n", token_id((*new)->item), ((t_token *)(*new)->item)->str);
	return (1);
}

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
		btree_debug(ast, parser_disp);
	else
	{
		printf("AST FAILED\n");
		control->quit = 1;
		ft_lstclear(&tklst, del_token);
		ft_dlstclearback_addr(&dlst, (void (*)(void **))&del_ast);
		return (NULL);
	}
	ft_lstremove_if(&tklst, NULL, tkcmp_braces, del_token);
	ft_lstclear(&tklst, NULL);
	ft_dlstclear(&dlst, NULL);
	btree_clear(&ast, del_token); // Line to delete for next step !
	return (ast);
}
