/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_cmd_assist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:34:33 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 11:34:59 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file assists the list_to_cmd_root.c file.
*/

/*
** note:	this function is called when we want to build the two linked lists
**			for the redirections and indirections fileds of the t_simple_cmd
**			structure.
**
** input:	a linked list of tokens. each time the first token is a redirection
**			operator and the following one is the name of the file.
**
** RETURN:	0 if malloc failed.
**			1 OK
*/

int		list_to_cmd_fill_redirections_fields(t_simple_cmd *cmd, t_list *tokens)
{
	int id;

	while (tokens)
	{
		id = tklst_id(tokens);
		if (id == GREAT || id == DGREAT || id == LESS)
		{
			if (!list_to_cmd_fill_redirections_fields2(cmd, id, tokens))
				return (0);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (1);
}

/*
** note:	this funciton will creat a new t_arrow struct and append it to
**			either cmd->indirection (LESS), or cmd->redirection (GREAT and
**			DGREAT).
**
** input:	the id of the current token, the str of the next token.
** RETURN:	1 OK
** 			0 KO
*/

int		list_to_cmd_fill_redirections_fields2(t_simple_cmd *cmd, int id, \
		t_list *tokens)
{
	t_arrow	*arrow;
	t_list	*new;
	char	**dest;

	if (!(arrow = init_t_arrow()))
		return (0);
	dest = &((t_token *)tokens->next->content)->str;
	arrow->dest = *dest;
	*dest = NULL;
	arrow->src = ((t_token *)tokens->content)->str;
	arrow->id = id;
	if (!(new = ft_lstnew(arrow)))
	{
		free_t_arrow(arrow);
		return (0);
	}
	if (id == LESS)
		ft_lstadd_back(&cmd->indirections, new);
	else
		ft_lstadd_back(&cmd->redirections, new);
	return (1);
}

/*
** note:	this function creates and bzero a t_arrow pointer.
*/

t_arrow	*init_t_arrow(void)
{
	t_arrow *arrow;

	if (!(arrow = malloc(sizeof(t_arrow))))
		return (NULL);
	ft_bzero(arrow, sizeof(t_arrow));
	return (arrow);
}

void	free_t_arrow(void *void_arrow)
{
	t_arrow *arrow;

	arrow = (t_arrow*)void_arrow;
	free(arrow->dest);
	free(arrow);
}
