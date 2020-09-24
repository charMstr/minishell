/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:30:01 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 11:30:16 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** note:	this function will try to match one input string str, with a second
**			string yes_star that will contain one or eventually more kleen star
**			operators.
** note:	we only call this funcion when we are in an unquoted section of a
**			string and if we meet a '*'. When starting this function,
**			yes_star[0] is '*', we skip all the adjacent '*'. Then we will to
**			to shift the ref string's index, until we fall back onto the same
**			character that directly follows the '*' in yes_star. in That case
**			we consider the '*' character did cover a portion of the string.
**
**			As soon as we have a match, we will go back and continue comparing
**			strings with the match_no_star function.
**			In order to cover the largest possibility of matches, we also
**			always try to recurse with the very next index on the ref string.
**
** input:	- str: could contain a star, but it would be a star that is just a
**			normal character.
**			- yes_star: string that contains a '*' at yes_star[0].
**			- quoted and offset: are just set to zero.
**
** RETURN:	1 match
**			0 no match or NULL inputs.
*/

int		match_star(char *ref, char *yes_star, int quoted, int offset)
{
	int i;
	int j;

	i = 0;
	j = 0;
	//printf("entering match star with yes_star[0] == %c\n", yes_star[0]);
	while (yes_star[j + 1] == '*')
		j++;
	if (!ft_strcmp(yes_star, "*"))
		return (1);
	if (yes_star[j + 1] == '\"' || yes_star[j + 1] == '\'')
	{
		quoted = yes_star[j + 1];
		offset++;
	}
	if (yes_star[j + offset + 1] == '\\' && !quoted)
		offset++;
	while (ref[i] && ref[i] != yes_star[j + offset + 1])
		i++;
	if (!ref[i])
		return (0);
	if (quoted)
		return (match_star(ref + i + 1, yes_star + j, 0, 0) \
			|| match_within_quote(ref + i, yes_star + j + offset + 1, quoted));
	return (match_star(ref + i + 1, yes_star + j, 0, 0) \
			|| match_no_star(ref + i, yes_star + j + 1, 0, 0));
}

/*
** note:	this funcion is called when we are in a quoted section, dealing
**			with a '\' cahracter met. just updating the esc_next var and
**			advancing the index j.
*/

void	match_within_quote_escape_met(int *j, char *str, int *esc_next)
{
	//printf("met a \\ in a quoted section\n");
	*esc_next = 1;
	if (str[*j + 1] && (str[*j + 1] == '\\' || str[*j + 1] == '$' \
		|| str[*j + 1] == '`' || str[*j + 1] == '\"' || str[*j + 1] == '\n'))
	{
		(*j)++;
	}
}

/*
** note:	this function is called when conparing the ref string and the
**			potential pathname string, in the case we meet a quoted section.
**
** note:	if the quote type is ', we simply compare the strings litterally
**			until we meet the matching '.
**			if we are between double quotes: we have to take care of the cases
**			of escaped sequences.
**
** RETURN:	0 KO, no match between strings
**			recursion, keep on compararing strings
*/

/*
**	printf("entering match_within_quote with:\nref[0] = %c\n"\
**		"str[0] == %c\n", ref[0], str[0]);
*/

int		match_within_quote(char *ref, char *str, char quote)
{
	int i;

	i = 0;
	if (quote == '\"')
		return (match_until_double_quote(ref, str, 0));
	while (ref[i] && str[i] && ref[i] == str[i] && str[i] != '\'')
		i++;
	if (!ref[i] && !str[i])
		return (1);
	if (str[i] && str[i] == '\'')
		return (match_no_star(ref + i, str + i + 1, 0, 0));
	return (0);
}

/*
** note:	this function will make sure the quoted string matches the ref
**			string untill either the of string or the quote char is met.
**
**			if this does not happen, we Return zero. else the job is not over,
**			we recurse and call match_no_star and keep comparing ref string and
**			the string in which we havent met a star yet.
**
** RETURN:	0 if mismatch
**			recursion result for further comparison elsewise.
*/

int		match_until_double_quote(char *ref, char *str, int esc_next)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (ref[i] && str[j])
	{
		if (str[j] == '\\')
			match_within_quote_escape_met(&j, str, &esc_next);
		else
			esc_next = 0;
		if (str[j] == '\"' && !esc_next)
			break ;
		if (ref[i] != str[j])
			return (0);
		i++;
		j++;
	}
	if (!ref[i] && !str[j])
		return (1);
	if (!esc_next && str[j] && str[j] == '\"')
		return (match_no_star(ref + i, str + j + 1, 0, 0));
	return (0);
}

/*
** note:	this function will try to match a ref string, with a string in
**			which we havent met an unquoted kleen star operator yet.
**			if the '*' is within quotes, or escaped, we simply consider it to
**			be a regular character.
**
** note:	if we meet quotes, we consider we enter a quoted section, but we
**			dont use the quote istself as a character compared against the ref
**			string.
**
** note:	if we meet a kleen star operator, we will enter a subfunction.
**
** input:	- ref, the ref string we are trying to compare with
**			- no_star, the string we are assessing
**			- esc_next, always set to 0
**			- j, 0
**
** RETURN:	1 OK
**			0 KO
*/

int		match_no_star(char *ref, char *no_star, int esc_next, int j)
{
	int i;

	i = 0;
	while (ref[i] && no_star[j])
	{
		if (!esc_next && (no_star[j] == '\'' || no_star[j] == '\"'))
			return (match_within_quote(ref + i, no_star + j + 1, no_star[j]));
		if (!esc_next && no_star[j] == '\\')
		{
			j++;
			esc_next = 1;
		}
		if (!esc_next && no_star[j] == '*')
			return (match_star(ref + i, no_star + j, 0, 0));
		else
			esc_next = 0;
		if (!esc_next && ref[i] != no_star[j])
			return (0);
		i++;
		j++;
	}
	if ((!ref[i] && !no_star[j]) || \
			(no_star[j] && ft_isonly(no_star + j, '*')))
		return (1);
	return (0);
}
