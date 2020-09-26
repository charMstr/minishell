/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_cmd_root.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:33:05 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 19:20:42 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** note:	This function will replace the token contained in an ast node, from
**			type LIST to type CMD. token->str then contains a t_simple_cmd ptr.
**
** note:	When doing a command like such:
**			echo HEYYY > hello1 > hello2 > hello3 >> world1 >> world2 >> world3
**			Only the final world3 file will contain "HEYYY" but all files are
**			created still. Thats why the t_simple_cmd structure contains a
**			linked lists of redirections.
**
** INPUT:	Token with a LIST id. (token->str contains a list of tokens of
**			type: TOKEN, GREAT, DGREAT or LESS.)
**
** RETURN:	1 OK
**			0 KO
*/

int				list_to_cmd_root(t_token *token_node)
{
	t_simple_cmd	*cmd;
	t_list			*tokens_list;
	t_list			*redirections;

	tokens_list = (t_list *)(token_node->str);
	if (!(cmd = init_t_simple_cmd()))
		return (0);
	redirections = list_to_cmd_skim_redirections(&tokens_list);
	if (!list_to_cmd_fill_argv_array(cmd, tokens_list))
	{
		ft_lstclear(&redirections, del_token);
		free_t_simple_cmd(cmd);
		return (0);
	}
	if (!list_to_cmd_fill_redirections_fields(cmd, redirections))
	{
		ft_lstclear(&redirections, del_token);
		free_t_simple_cmd(cmd);
		return (0);
	}
	ft_lstclear(&redirections, del_token);
	ft_lstclear(&tokens_list, del_token);
	token_node->str = (char *)cmd;
	token_node->id = CMD;
	return (1);
}

/*
** note:	this function will separate the redirections and its following
**			token from the command token. the original linked list will only
**			contain the remaining tokens concerning argv afterall
**
** RETURN:	a linked list containing only the the redirections related tokens.
*/

t_list			*list_to_cmd_skim_redirections(t_list **tokens)
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

void			free_t_simple_cmd(void *void_cmd)
{
	t_simple_cmd *cmd;

	cmd = (t_simple_cmd*)void_cmd;
	ft_array_free(cmd->argv, ft_array_len(cmd->argv));
	ft_lstclear(&cmd->arrows, free_t_arrow);
	free(cmd);
}

/*
** note:	this function is called to creat a 2d array and put it into the
**			argv field of the t_simple_cmd struct.
**			the cmd->argv_list is browsed, and one by one the str pointer
**			fields are copied into the array, and then set to NULL.
**
** RETURN:	1 OK
**			0 OK
*/

int				list_to_cmd_fill_argv_array(t_simple_cmd *cmd, t_list *tokens)
{
	int		size;
	int		index;
	t_list	*copy;

	copy = tokens;
	size = 0;
	index = 0;
	while (copy)
	{
		copy = copy->next;
		size++;
	}
	if (!(cmd->argv = malloc(sizeof(char *) * (size + 1))))
		return (0);
	cmd->argv[size] = NULL;
	while (tokens)
	{
		cmd->argv[index] = ((t_token *)tokens->content)->str;
		((t_token *)tokens->content)->str = NULL;
		tokens = tokens->next;
		index++;
	}
	return (1);
}
