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
	int i;
	int fd = 1;
	char *str;

	if (token_id(node) == LIST)
		str = (char [5]){'l', 's', 't', 47 + ft_lstsize((t_list *)node->str), '\0'};
	else if (token_id(node) == SUBSHELL)
		str = "shell";
	else
		str = (node ? node->str : "null");
//	int len = ft_strlen(str);

	i = -1;
	ft_putstr_fd("[", fd);
	while (++i < SIZE_LEAF - 2 && str[i])
		ft_putchar_fd(str[i], fd);
	while (i++ < SIZE_LEAF - 2)
		ft_putchar_fd(' ', fd);

	ft_putstr_fd("]", fd);
	(void)parent;
}