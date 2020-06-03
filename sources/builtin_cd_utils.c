/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 22:23:43 by mli               #+#    #+#             */
/*   Updated: 2020/06/03 23:30:38 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file is a subset of the builtin_cd.c file.
** this file will take care of the builtin cd
*/

/*
** To be used with strerror(errno) or "string\n"
*/

int		ft_print_error(char *cmd, char *param, char *str)
{
	ft_putstr_fd("\033[0;91mminishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (param)
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(param, 2);
		ft_putstr_fd("': ", 2);
	}
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
	return (-1);
}

void	ft_ls(char *directory, int showdot)
{
	struct dirent	*reader;
	DIR				*dir;
	int				i;

	i = 1;
	if (!(dir = opendir(directory)))
	{
		printf("Couldn't read this directory (%s)\n", directory);
		return ;
	}
	while ((reader = readdir(dir)) != NULL)
	{
		if (!(showdot == 0 && reader->d_name[0] == '.'))
		{
			ft_putstr_fd("\033[0;93m", 1);
			ft_putstr_fd(reader->d_name, 1);
			ft_putstr_fd("\033[0m", 1);
			ft_putstr_fd((i++ % 3 != 0 ? "     \t\t" : "\n"), 1);
		}
	}
	ft_putstr_fd(((i - 1) % 3 == 0 ? "" : "\n"), 1);
	closedir(dir);
}

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
