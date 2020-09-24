/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_matched_add_to_list.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 17:33:26 by charmstr          #+#    #+#             */
/*   Updated: 2020/09/24 20:46:33 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
** this file takes care of creating a new token for a pathname that got
** validated. the token is inserted in a temporary linked list.
*/

/*
** note:	This function will be called when we finished validating all the
**			path parts. we can now creat a new token containing this string and
**			add it into the temporary linked list matched_paths.
**
** note:	we also need to check and update the flags first_match and
**			is_filename
**
** RETURN:	0, OK.
**			1, ambiguous redirect.
**			2, fatal error.
*/

int	pathname_matched_add_to_list(t_path_exp *tool, char *path)
{
	t_token *new_token;
	t_list	*new_link;

	if (tool->first_match == 1 && tool->is_filename)
		return (1);
	if (!tool->first_match)
		tool->first_match = 1;
	if (!(new_token = lexer_init_token()))
		return (2);
	if (!(new_token->str = ft_strdup(path)))
	{
		free(new_token);
		return (2);
	}
	if (!(new_link = ft_lstnew(new_token)))
	{
		free(new_token->str);
		free(new_token);
		return (2);
	}
	ft_lstadd_back(&tool->matched_paths, new_link);
	return (0);
}

