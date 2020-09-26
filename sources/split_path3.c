/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 19:32:30 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 20:05:13 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file contains the functions that will unquote the path_parts we
** collected in a linked list, before we can compare to the folders and files
** names. it also build the linked list of ints, stating which '*' is a valid
** wildcar.
*/

/*
**	note:	this function will unquote the path_part string in the link we
**			just created. plus it will create a link list of ints,
**			corresponding to the indexes of the kleen start operators that
**			were unquoted (valid) in this path_part.
**
**	RETURN:	1 OK
**			0 KO
*/

int		path_part_unquoting(t_path_part *new, char *str)
{
	int i;
	int esc_next;

	i = -1;
	esc_next = 0;
	while (str[++i])
	{
		if (!esc_next && str[i] == '\\')
		{
			esc_next = 1;
			path_part_unquoting_escape_char(str, &i, new->quoted);
			continue;
		}
		if (str[i] == '*' && !esc_next && !new->quoted)
		{
			if (!add_index_valid_kleen_star_to_lst(new, i))
				return (0);
		}
		else if (!esc_next && (str[i] == '\'' || str[i] == '"'))
			path_part_unquoting_assist(str[i], &new->quoted, str, &i);
		esc_next = 0;
	}
	return (1);
}

/*
** note:	this function is in charge of toggling the quoted flag.
**			if we notice that we matche a quote character that was activated,
**			we can unset the flag.
**			also each time we come accross a quote that is the begining or the
**			end of the quoted section, we eat the char and actualise the index.
*/

void	path_part_unquoting_assist(char c, char *quoted, char *str, int *index)
{
	if (!*quoted)
	{
		*quoted = c;
		ft_strcdel(str, *index);
		(*index)--;
		return ;
	}
	else if (c == quoted[0])
	{
		ft_strcdel(str, *index);
		(*index)--;
		quoted[0] = 0;
	}
}

/*
**	note:	this function is called when we met an escape character. depending
**			if we are in a quoted section or not, the behavior is slighly
**			different. inside quotes, we only eat the current char if the
**			next character is also a '\\' character, otherwise it is considered
**			a regular character.
**			outsise quotes, we eat the current character no matter what.
*/

void	path_part_unquoting_escape_char(char *str, int *i, char quoted)
{
	if (quoted)
	{
		if (str[*i + 1] && str[*i + 1] == '\\')
		{
			ft_strcdel(str, *i);
			(*i)--;
		}
		return ;
	}
	ft_strcdel(str, *i);
	(*i)--;
}

/*
** note:	this function will add the index of a valid kleen star to a linked
**			list specialy dedicated to the task in the t_path_part struct,
**			calle star_index.
**
** RETURN:	1, OK
**			0 KO
*/

int		add_index_valid_kleen_star_to_lst(t_path_part *new, int index)
{
	int		*i;
	t_list	*new_star_index;

	if (!(i = malloc(sizeof(int))))
		return (0);
	*i = index;
	if (!(new_star_index = ft_lstnew((void*)i)))
	{
		free(i);
		return (0);
	}
	ft_lstadd_back(&(new->star_index), new_star_index);
	return (1);
}
