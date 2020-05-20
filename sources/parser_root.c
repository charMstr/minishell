#include "minishell.h"

void		parser_disp(t_token *node)
{
	int i;
	int fd = 1;
	char *str = (node ? node->str : "null");
//	int len = ft_strlen(str);

	i = -1;
	ft_putstr_fd("[", fd);
	while (++i < SIZE_LEAF - 2 && str[i])
		ft_putchar_fd(str[i], fd);
	while (i++ < SIZE_LEAF - 2)
		ft_putchar_fd(' ', fd);

	ft_putstr_fd("]", fd);
}

void		del_ast(t_btree **node)
{
	if (!*node)
		return ;
	del_ast(&(*node)->left);
	del_ast(&(*node)->right);
	if (!(*node)->left && !(*node)->right)
	{
//		printf("DEL: [%s]\n", ((t_token *)(*node)->item)->str);
		ft_free((void **)node);
	}
}

int			token_id(t_token *token)
{
	if (!token)
		return (-1);
	return (token->id);
}

void		ast_add(t_btree **ast, t_btree *add)
{
		if (*ast == NULL)
			*ast = add;
		else if ((*ast)->left == NULL)
			(*ast)->left = add;
		else if ((*ast)->item == NULL)
			(*ast)->item = add->item;
		else if ((*ast)->right == NULL)
			(*ast)->right = add;
		else
		{
			add->left = *ast;
			*ast = add;
		}
}

// For specifying special state for cmds (in, maybe, a struct), ex : job &
int			parser_special_state(t_list *lst, t_btree *new)
{
	(void)lst; (void)new;

	return (1);
}

t_btree		*parser_root(t_list *tokens, t_control *control)
{
	t_btree		*ast;
	t_btree		*tmp;
	t_dlist		*dlst;
	ast = NULL;

	if (!(dlst = ft_memalloc(sizeof(*dlst))))
		return (NULL);
	ft_free((void **)&dlst);

	ast_add(&ast, btree_new(NULL));
	while (tokens)
	{
//		printf("%d\n", token_id(tokens->content));
		tmp = btree_new(tokens->content);
		ast_add(&ast, tmp);
		if (token_id(tokens->content) == TOKEN &&
				tokens->next &&
				token_id(tokens->next->content) == TOKEN)
		{
			tokens = tokens->next;
			// node->left =  linked list containing parameters
			while (tokens && token_id(tokens->content) == TOKEN)
				tokens = tokens->next;
//			if (tmp->left == NULL)
//				tmp->left = btree_new(NULL);
			if (tokens && token_id(tokens->content) == AND)
			{
				tmp->right = btree_new(tokens->content);
				tokens = tokens->next;
			}
//			else
//				tmp->right = btree_new(NULL);
		}
		else
			tokens = tokens->next;
	}

	btree_debug(ast, parser_disp);

	del_ast(&ast);
	return (ast);
	(void)tokens;
	(void)control;
}
