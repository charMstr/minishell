#include "minishell.h"

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

int	simple_cmd_convert2(t_token *token_node)
{
	t_simple_cmd *cmd;
	t_list *tokens_list;
	t_list *redirections;

	tokens_list = (t_list *)(token_node->str);
	if (!(cmd = simple_cmd_init()))
		return (0);
	redirections = simple_cmd_skim_redirections(&tokens_list);
	/* OK
	printf("for the command words:\n");
	debug_tokens_list(tokens_list);
	printf("for the redirections:\n");
	debug_tokens_list(redirections);
	*/
	if (!simple_cmd_fill_argv_field(cmd, tokens_list))
	{
		ft_lstclear(&redirections, del_token);
		free_simple_cmd_struct(cmd);
		return (0);
	}
	if (!simple_cmd_fill_redirections_fields(cmd, redirections))
	{
		ft_lstclear(&redirections, del_token);
		free_simple_cmd_struct(cmd);
		return (0);
	}
	ft_lstclear(&redirections, del_token);
	ft_lstclear(&tokens_list, del_token);
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

t_list *simple_cmd_skim_redirections(t_list **tokens)
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
t_simple_cmd	*simple_cmd_init(void)
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

void	free_simple_cmd_struct(t_simple_cmd *cmd)
{
	ft_array_free(cmd->argv, ft_array_len(cmd->argv));
	ft_lstclear(&cmd->redirections, free_t_arrow);
	ft_lstclear(&cmd->indirections, free_t_arrow);
	free(cmd);
}
