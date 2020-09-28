/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 22:23:43 by mli               #+#    #+#             */
/*   Updated: 2020/09/28 10:54:11 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file is a subset of the builtin_cd.c file.
** this file will take care of the builtin cd
*/

/*
** note : Fills target with the current path (getcwd)
**	If the new path does not fit in the current buffer, errno is raised
**	so we erase it, and let getcwd allocate a new buffer containing the new path
**
** RETURN:	1 on success
**			0 if an error occured
*/

int		ft_getcwd(char **target)
{
	if (!(getcwd(*target, ft_strlen(*target))))
	{
		errno = 0;
		ft_free((void **)target);
		if (!(*target = getcwd(NULL, 0)))
			return (0);
	}
	return (1);
}
