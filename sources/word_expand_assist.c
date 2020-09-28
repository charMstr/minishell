/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expand_assist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 10:30:50 by charmstr          #+#    #+#             */
/*   Updated: 2020/09/28 10:33:32 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file assist the word_expand_root.c file
*/

/*
** note:	this function will skim the linked list of tokens after the
**			parameter expansion occured. it will destroy links that contains an
**			empty string. therefore those tokens are not part of the argv list
**			anymore. they are destroyed at this stage (before the unquoting etc
**			) so that we still make a difference between:
**			echo "" salut
**				and
**			echo $empty_var salut
*/

void	skim_empty_tokens(t_list **tokens)
{
	t_list	*del_me;

	while (*tokens)
	{
		if (!ft_strlen(((t_token *)((*tokens)->content))->str))
		{
			del_me = *tokens;
			*tokens = (*tokens)->next;
			del_token((t_token *)(del_me->content));
			free(del_me);
		}
		else
			tokens = &(*tokens)->next;
	}
}
