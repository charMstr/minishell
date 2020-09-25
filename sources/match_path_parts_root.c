/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_path_parts_root.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 18:14:36 by charmstr          #+#    #+#             */
/*   Updated: 2020/09/24 20:51:29 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
** this file is in charge of matching the path_parts, one after another.
** the path_parts have been splited around the '/' characters already, so we
** just have a string corresponding to a directory or a filename. the string
** has benn cleaned as much as possible so any escaping or quoting character
** has been removed. to distinguish the '*' that are to be taken litteraly or
** that are wild cards, we refer to a linked list containing the index of the
** wild cards.
*/

/*
**	note:	this function will try to find an answer to a possible match
**			between the two strings. the string from the path_parts linked list
**			'current link called str is accompanied with a linked list stating
**			which kleen star operator is valid and not just a character.
**
**	inputs:	ref, the d_name from a directory stream we opened.
**			paht_parts, containing the string to compare to ref, and the linked
**				list of all the valid wildcards indexe.
**
** RETURN:	1, match!
**			0, no match.
*/

int	match_path_part_root(t_list *path_parts, char *ref)
{
	t_list		*wild_cards;
	t_strings	strings;

	strings.str = ((t_path_part *)(path_parts->content))->path_part;
	strings.ref = ref;
	wild_cards = ((t_path_part *)(path_parts->content))->star_index;
	if (!strings.str || !strings.ref)
		return (0);
	if (!wild_cards)
	{
		if (!ft_strcmp(strings.str, strings.ref))
			return (1);
		return (0);
	}
	else
		return (match_path_part(strings, wild_cards, 0, 0));
}

/*
** note:	this function will try to match a ref string and a str that surely
**			contains a valid kleen start operator
**
** RETURN:	1, match
**			0, no match
*/

int	match_path_part(t_strings strs, t_list *wild_cards, int i, int j)
{
	while (strs.str[i] && strs.ref[j] && (strs.str[i] == strs.ref[j]))
	{
		if (strs.str[i] == '*' && match_path_check_valid_star(wild_cards, i))
			break;
		i++;
		j++;
	}
	if (ft_isonly(strs.str + i, '*') || (!strs.str[i] && !strs.ref[j]))
		return (1);
	if (!strs.ref[j] || !strs.str[i] || strs.str[i] != '*')
		return (0);
	while (strs.str[i + 1] == '*')
		i++;
	while (strs.ref[j] && strs.ref[j] != strs.str[i + 1])
		j++;
	if (!strs.ref[j])
		return (0);
	return (match_path_part(strs, wild_cards, i, j + 1) \
		|| match_path_part(strs, wild_cards, i + 1, j));
}

/*
** note:	this function will be called when we meet a '*' character in str,
**			we will check if its index belong in the linked list of the valid
**			kleen stars of the string.
**
** RETURN:	1, valid kleen star
**			0, not valid (was an escaped character)
*/

int	match_path_check_valid_star(t_list *wild_cards, int index)
{
	while (wild_cards)
	{
		if (*((int*)(wild_cards->content)) == index)
			return (1);
		wild_cards = wild_cards->next;
	}
	return (0);
}
