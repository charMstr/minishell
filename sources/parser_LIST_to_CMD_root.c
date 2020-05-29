#include "minishell.h"

/*
** note:	This function will parcour the ast in a postorder manner, and
**			recognise if the current tree node is containing the type LIST in
**			its content. If yes it then applies a function to convert the node
**			type into a CMD, Which now contains a t_simple_cmd in its char *str
**			field.
**
** return:	1 OK
**			0 KO
*/

int	parser_LIST_to_CMD_root(t_btree* ast, t_control *control)
{
	int res;

	if (!ast)
		return (1);
	//debug_node_id(ast);
	if ((res = parser_LIST_to_CMD_root(ast->left, control)))
		res = parser_LIST_to_CMD_root(ast->right, control);
	if (res && btree_id(ast) == LIST)
		res = parser_LIST_to_CMD1((t_token *)ast->item);
	if (!res)
		control->quit = 1;
	return (res);
}

/*
** note:	This function will replace the token contained an ast node, from
**			type LIST to type CMD. token->str then contains a t_simple_cmd ptr.
**
** note:	When doing a command like such:
**			echo HEYYY > hello1 > hello2 > hello3 >> world1 >> world2 >> world3
**			Only the final world3 file will contain "HEYYY" but all files are
**			created still. Thats why the t_simple_cmd structure contains a
**			linked list for the stdout redirection, and one for the stdin.
**
** INPUT:	Token with a LIST id. (token->str contains a list of tokens of
**			type: WORD, GREAT, DGREAT or LESS.)
**
** RETURN:	1 OK
**			0 KO
*/

int	parser_LIST_to_CMD1(t_token *token_node)
{
	t_simple_cmd *cmd;
	t_list *tokens_list;
	t_list *redirections;

	tokens_list = (t_list *)(token_node->str);
	if (!(cmd = init_t_simple_cmd()))
		return (0);
	redirections = parser_LIST_to_CMD_skim_redirections(&tokens_list);
	/* OK
	printf("for the command words:\n");
	debug_tokens_list(tokens_list);
	printf("for the redirections:\n");
	debug_tokens_list(redirections);
	*/
	if (!parser_LIST_to_CMD_fill_redirection_fields(cmd, redirections))
	{
		ft_lstclear(&redirections, del_token);
		free_t_simple_cmd(cmd);
		return (0);
	}
	cmd->argv_list = tokens_list;
	ft_lstclear(&redirections, del_token);
	token_node->str = (char *)cmd;
	token_node->id = CMD;
	//debug_simple_cmd(cmd);
	return (1);
}

/*
** note:	this function will separate the redirections and its following
**			token from the command token. the original linked list will only
**			contain the remaining tokens concerning argv afterall
**
** RETURN:	a linked list containing only the the redirections related tokens.
*/

t_list *parser_LIST_to_CMD_skim_redirections(t_list **tokens)
{
	t_list *redirections;
	t_list *couple;

	redirections = NULL;
	while (*tokens)
	{
		if (tklst_id(*tokens) == GREAT || tklst_id(*tokens) == DGREAT \
					|| tklst_id(*tokens) == LESS)
		{
			couple = *tokens;
			*tokens = (*tokens)->next->next;
			couple->next->next = NULL;
			ft_lstadd_back(&redirections, couple);
		}
		else
			tokens = &(*tokens)->next;
	}
	return (redirections);
}

/*
** note:	this function will init a structure of type t_simple_cmd.
**
** RETURN:	pointer to malloced struct.
**			NULL if failure.
*/
t_simple_cmd	*init_t_simple_cmd(void)
{
	t_simple_cmd *cmd;

	if (!(cmd = malloc(sizeof(t_simple_cmd))))
		return (NULL);
	ft_bzero(cmd, sizeof(t_simple_cmd));
	return (cmd);
}

/*
** note:	this function will free the memory taken by a struct of this type.
*/

void	free_t_simple_cmd(void *void_cmd)
{
	t_simple_cmd *cmd;

	cmd = (t_simple_cmd*)void_cmd;
	ft_array_free(cmd->argv, ft_array_len(cmd->argv));
	ft_lstclear(&cmd->argv_list, del_token);
	ft_lstclear(&cmd->redirections, free_t_arrow);
	ft_lstclear(&cmd->indirections, free_t_arrow);
	free(cmd);
}
