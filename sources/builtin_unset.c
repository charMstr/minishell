/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 10:07:47 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 10:07:48 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file is a subset of the builtin_root.c file.
** It takes care of the unset builtin.
*/

/*
** note:	the unset can take more than one argument, therefore we will loop
**			over each of them.
**
** note:	we assume that we do call the function with the argv[0] as being
**			the builtin name. so we start with arg argv[1].
**
** note:	set the exit_status to 0 if everytihng ok, or 1 if at least one of
**			the unset identifiers was wrong, starting by a forbidden character.
**
** RETURN:	1 always. because no fatal error possible.
*/

int		unset_builtin(t_list **env_head, char **argv, t_control *control)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (!is_identifier_valid(argv[i], "unset"))
			unset_in_env_list(env_head, argv[i]);
		else
			control->exit_status = 1;
		i++;
	}
	return (1);
}

/*
** note:	this function will try to find a matching label in the linked list
**			and remove it.
** note:	if the link is found, note: that we use *ptr (and not ptr) to
**			really afect the list (*ptr = (*ptr)->next). And we free the link
**			and set it to NULL. Terefore if it is the last link, the head of
**			the list is set to NULL.
*/

void	unset_in_env_list(t_list **env_head, char *str)
{
	t_list **ptr;
	t_list *extra;

	ptr = env_head;
	while (*ptr)
	{
		if (!ft_strncmp(str, ((t_env*)((*ptr)->content))->label, \
					ft_strlen(str) + 1))
		{
			extra = *ptr;
			*ptr = (*ptr)->next;
			env_del_struct(extra->content);
			free(extra);
			return ;
		}
		ptr = &(*ptr)->next;
	}
}

/*
** note:	this function will check that the identifer is ok, when passed to
**			unset or export builtin command.
**
** note:	the message is displayed on the standard error when the first char
**			of the identifier is either:
**			@, ~, %, ^, *, +, =, \, /, ?, ',' or '.'
**
** input:	- command: command name to display in case of error message
**			- the identifier string.
**
** RETURN:	0 OK
**			1 KO therefore we can assign the returned value directly in the
**			control->exit_status variable.
*/

int		is_identifier_valid(char *identifier, char *command)
{
	if (ft_stristr(identifier, "@~%^*+=\\/?,.") == 0)
	{
		ft_perror(command, identifier, "not a valid identifier");
		return (1);
	}
	return (0);
}
