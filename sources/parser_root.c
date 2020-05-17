#include "minishell.h"

void		parser_disp(t_token *node)
{
	int i;
	int fd = 1;
	char *str = node->str;
//	int len = ft_strlen(str);

	if (!node)
	{
		ft_putstr_fd("[null]", fd);
		return ;
	}
	ft_putstr_fd("[", fd);

	i = -1;
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

t_btree		*parser_root(t_list *tokens, t_control *control)
{
	t_btree		*ast;
	t_btree		*tmp;
	t_dlist		*dlst;
	ast = NULL;

	if (!(dlst = ft_memalloc(sizeof(*dlst))))
		return (NULL);
	ft_free((void **)&dlst);

	while (tokens)
	{
		tmp = btree_new(tokens->content);
		if (ast == NULL)
			ast = tmp;
		else if (ast->left == NULL)
			ast->left = tmp;
		else if (ast->right == NULL)
			ast->right = tmp;
		else // Add btreefront
		{
			tmp->left = ast;
			ast = tmp;
		}
		tokens = tokens->next;
	}

//	btree_debug(ast, parser_disp);

	del_ast(&ast);
	return (ast);
	(void)tokens;
	(void)control;
}
