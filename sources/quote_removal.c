/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:18:24 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 11:18:26 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** note:	this function will be called when we are on an unquoted section of
**			the string. (therefor called at the very beggining)
**			backslash are collapsed by a memmove and then the next char is
**			considered escaped so we skip it.
** input:	i - index in str.
**			str - the string.
*/

void	quote_removal_unquoted_part(char *str, int i, t_no_unquote *no)
{
	while (str[i])
	{
		if (i == no->start)
			if (!quote_removal_skip_protected_part(str, &i, no))
				return ;
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'')
			{
				if (!quote_removal_eat_char(str, &i, no))
					return ;
				while (str[i] && str[i] != '\'')
					i++;
				if (!quote_removal_eat_char(str, &i, no))
					return ;
			}
			else
				return (quote_removal_doubly_quoted_part(str, i, no));
		}
		if (str[i] && str[i] == '\\')
			if (!quote_removal_eat_char(str, &i, no))
				return ;
		i++;
	}
}

/*
** note:	this function is called when we met an unescaped and unquoted
**			double quote.
*/

void	quote_removal_doubly_quoted_part(char *str, int i, t_no_unquote *no)
{
	if (!quote_removal_eat_char(str, &i, no))
		return ;
	while (str[i])
	{
		if (i == no->start)
			if (!quote_removal_skip_protected_part(str, &i, no))
				return ;
		if (str[i] && str[i] == '\"')
		{
			if (!quote_removal_eat_char(str, &i, no))
				return ;
			return (quote_removal_unquoted_part(str, i, no));
		}
		if (str[i] == '\\' && str[i + 1] && (str[i + 1] == '\\' \
				|| str[i + 1] == '\"' || str[i + 1] == '$' \
				|| str[i + 1] == '\n' || str[i + 1] == '`'))
			if (!quote_removal_eat_char(str, &i, no))
				return ;
		i++;
	}
}

/*
** note:	this function will simply skip the protected part
**
** return:	1 we can keep going
**			0 we reach the end
*/

int		quote_removal_skip_protected_part(char *str, int *i, t_no_unquote *no)
{
	if (!str[*i])
		return (0);
	while (str[*i] && *i < no->end)
		(*i)++;
	if (!str[*i])
		return (0);
	return (1);
}

/*
** note:	this function will collapse the string on itself, eating the
**			current char, and updating the protected start and en accordingly.
** note:	while updating no->start, the current char can become a protected
**			char, so we need to skip the section.
** return:	1 we can keep going
**			0 end of string reached.
*/

int		quote_removal_eat_char(char *str, int *i, t_no_unquote *no)
{
	if (!str[*i])
		return (0);
	ft_memmove(str + *i, str + *i + 1, ft_strlen(str + *i));
	no->end--;
	no->start--;
	if (*i == no->start)
	{
		return (quote_removal_skip_protected_part(str, i, no));
	}
	return (1);
}

/*
** note:	this function will remove the quotes on a string. no need to
**			malloc here as we can collapse the string on itself as we need.
**
** note:	Within single quotes, nothing is changed.
**			Within double quotes, only the "\\" becomes a '\'
**			Otherwise, the '\' is always collapsed and replaced by the next
**			char.
** note:	the token->unquote_start and end have been created so that we can
**			protect some sections againt unquoting. especially the section
**			originating from parameter expansion.
**			token->unquote_end is put to -1 if it is not used
*/

void	quote_removal(t_token *token)
{
	t_no_unquote no;

	//debug_unquote(token);
	if (token->unquote_protected == 1)
	{
		no.start = token->protect_s;
		no.end = token->protect_e;
	}
	else
	{
		no.start = -1;
		no.end = -1;
	}
	quote_removal_unquoted_part(token->str, 0, &no);
	//printf("str after quote removal: [%s]\n", str);
}
