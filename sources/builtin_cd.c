/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 22:29:48 by mli               #+#    #+#             */
/*   Updated: 2020/07/02 16:48:46 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file is a subset of the the builtin_root.c file.
** this file will take care of the builtin cd
*/

/*
** note:	this implementation of the cd builtin supports no option
** note:	cd look only on the first arg, and don't treat the others
** note:	we assume the argv[0] is the name of the utility.
**
** RETURN:	1 on success
**			0 if an error occured (malloc) and quit
**			-1 if an error occured (chdir/env var not set) but don't quit
*/

int		cd_builtin(t_list *env, char **argv, t_control *control)
{
	int ret;

	if (!argv[1] || !ft_strcmp("~", argv[1]))
		ret = cd_special("HOME", env, control);
	else if (!ft_strcmp("-", argv[1]))
	{
		if ((ret = cd_special("OLDPWD", env, control)) == 1)
			ft_putendl_fd(control->cwd, STDOUT_FILENO);
	}
	else
		ret = ft_chdir(argv[1], env, control);
	if (ret == 0)
		control->quit = 1;
	else if (errno)
		ft_perror(argv[0], argv[1], strerror(errno));
	control->exit_status = (ret == 1 ? 0 : 1);
	return (ret == 0 ? 0 : 1);
}

/*
** note : It treats special cases :
**	- cd    => go to $HOME
**	- cd -  => go to $OLDWPD
**	Prints an error if the env variable is not set
*/

int		cd_special(char *envdir, t_list *env, t_control *control)
{
	char *dir;

	if (!(dir = env_get(envdir, ft_strlen(envdir), env)))
	{
		ft_perror("cd", envdir, "environment variable not set");
		return (-1);
	}
	return (ft_chdir(dir, env, control));
}

/*
** note : Here the directory change is performed
**		chdir is performed
**		OLDPWD is updated if needed,
**		control->cwd is always updated as it tracks the real cwd
**		Finally, the PWD is updated if needed
**
** RETURN:	1 on success
**			0 if an error occured (malloc)
**			-1 if an error occured (chdir)
*/

int		ft_chdir(char *target_dir, t_list *env, t_control *control)
{
	char	**oldpwd;
	char	**pwd_env;

	pwd_env = env_get_addr("PWD", 3, env);
	oldpwd = env_get_addr("OLDPWD", 6, env);
	if (chdir(target_dir) == -1)
		return (-1);
	if (oldpwd)
	{
		free(*oldpwd);
		if (!(*oldpwd = ft_strdup(control->cwd)))
			return (0);
	}
	if (!(ft_getcwd(&control->cwd)))
		return (0);
	if (pwd_env && ft_getcwd(pwd_env) == 0)
		return (0);
	return (1);
}
