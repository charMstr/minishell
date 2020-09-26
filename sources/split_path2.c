/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 20:12:37 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 20:12:38 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file contains the other functions related to split_path_root.c
*/

/*
** note:	this function will simply creat a link and add it to the linked
**			list of path_parts. it stores the string in the path_part
**			and initialise the rest.
**
** RETURN:	1 OK
**			0 KO
*/

int			add_path_part(char *str, t_list **path_parts, char quoted)
{
	t_path_part	*path_part;
	t_list		*new_link;

	if (!(path_part = init_path_part_link(str, quoted)))
	{
		free(str);
		return (0);
	}
	if (!path_part_unquoting(path_part, path_part->path_part))
	{
		delete_path_part_link(path_part);
		return (0);
	}
	if (!(new_link = ft_lstnew(path_part)))
	{
		delete_path_part_link(path_part);
		return (0);
	}
	ft_lstadd_back(path_parts, new_link);
	return (1);
}

/*
** note:	this function will initialise a path_part link
**
** RETURN:	pointer, OK
**			NULL KO
*/

t_path_part	*init_path_part_link(char *str, char quoted)
{
	t_path_part *new;

	if (!str)
		return (NULL);
	if (!(new = (t_path_part *)malloc(sizeof(t_path_part))))
		return (NULL);
	new->path_part = str;
	new->star_index = NULL;
	new->quoted = quoted;
	return (new);
}

/*
** note:	this function will delete the t_path_part structure.
*/

void		delete_path_part_link(void *content)
{
	t_path_part *elem;

	elem = (t_path_part *)content;
	free(elem->path_part);
	ft_lstclear(&(elem->star_index), free);
	ft_free((void **)&elem);
}
