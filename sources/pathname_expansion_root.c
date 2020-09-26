/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion_root.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 19:21:18 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 19:31:26 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file is the root file for the pathname expansion:
**		ex: y* -> yo.txt yeah.txt yes.txt
**
** we initially had a simple command. we choose one token and started expansion
** which resulted in a temporary linked list (multiple tokens could have
** resulted from  word expansion with field splitting).
** We will loop over this linked list and for each token assess if it contains
** at least one unquoted kleen star operator (it means pathname is expandable).
** If not we just call the quote removal function.
** If yes, the string is unquoted somehow, then either:
**			- no matches with filenames. the unquoted version of the token is
**				replacing itself in the list.
**			- at least one match. the new linked list in inserted in place as
**				well.
**			- more than one. do as above but need to make sure we are not in
**				the case of a filename replacement, otherwise error message is
**				displayed.
*/

/*
** note:	we are going to loop over each link of the linked list resulting
**			from the stage1 expansion of a token (ie. after word expansion and
**			field splitting), and each time assess if the pathname
**			expansion should be done.
**			If yes, we build a new linked list from the expansion of the
**			link/token/string and replace it in situ.
**
** inputs:	- token list.
**			- is_filename.
**
** RETURN:	0, Ok
**			1, KO, ambiguous redirect
**			2, KO, fatal error
*/

int		pathname_expansion_root(t_list **tokens, int is_filename)
{
	int res;

	while (*tokens)
	{
		if (!pathname_is_expandable(((t_token*)(*tokens)->content)->str))
			quote_removal((t_token*)(*tokens)->content);
		else
		{
			if ((res = pathname_expansion(&tokens, is_filename)))
				return (res);
		}
		tokens = &((*tokens)->next);
	}
	return (0);
}

/*
** note:	for a given token and its string, we assess if yes or no we should
**			operate a pathname expansion, is there an unquoted kleen star
**			operator?
**
** RETURN:	1 yes
**			0, no
*/

int		pathname_is_expandable(char *str)
{
	int quoted;
	int	escaped;
	int i;

	quoted = 0;
	escaped = 0;
	i = 0;
	while (str[i])
	{
		if (!escaped && str[i] == '\\')
		{
			i++;
			escaped = 1;
			continue;
		}
		if (!escaped && !quoted && (str[i] == '\"' || str[i] == '\''))
			quoted = str[i];
		else if (!escaped && quoted && str[i] == quoted)
			quoted = 0;
		else if (!escaped && !quoted && str[i] == '*')
			return (1);
		escaped = 0;
		i++;
	}
	return (0);
}

/*
** note:	this function will expand the pathname with the starting point
**			of the current token. this current token isnt modified until the
**			end. Either we succeffully created a new list of tokens containing
**			new	path-names, we therefor replace the original token with those
**			new filesnames. Or no filename matched and we simply unquote the
**			original token.
** note:	If more than one token is created and is_filename is 1 an ambiguous
**			redirect message is displayed.
**
** note:	we are going to creat a structure containing all the material
**			for pathname_expansion.
**			then we will call a recursive function that will attempt to
**			build a linked list of filenames (pathnames) as it goes.
**
** inputs:	- the token adress, needs to be replaced by the new linked list.
**				3 stars so we can update the adress in the loop that called
**				this function.
**			is_filename. used for ambiguous redirect warnings...
**
** RETURN:	0, OK
**			1, KO, ambiguous redirect.
**			2, fatal error.
*/

int		pathname_expansion(t_list ***token, int is_filename)
{
	t_list		*path_parts;
	t_path_exp	tool;
	int			res;

	if (!(path_parts = split_path_root(((t_token*)((**token)->content))->str)))
		return (2);
	init_path_expansion_struct(path_parts, &tool, is_filename);
	if ((res = pathname_matching_root(&tool, path_parts)))
	{
		ft_lstclear(&(tool.path_parts), delete_path_part_link);
		ft_lstclear(&(tool.matched_paths), del_token);
		return (res);
	}
	ft_lstclear(&(tool.path_parts), delete_path_part_link);
	if (!tool.matched_paths)
		quote_removal((t_token*)(**token)->content);
	else
	{
		word_expand_replace(token, tool.matched_paths);
		ft_lstclear(&(tool.path_parts), delete_path_part_link);
	}
	return (0);
}

/*
** note:	this funcion will create the strucure need to do the pathname
**			expansion. it contains among other things, the linkes list that has
**			in it all the path_parts previously splited and unquoted.
*/

void	init_path_expansion_struct(t_list *path_parts, t_path_exp *tool,\
		int is_filename)
{
	tool->path_parts = path_parts;
	tool->is_filename = is_filename;
	tool->first_match = 0;
	tool->matched_paths = NULL;
}
