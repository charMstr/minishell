/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 22:29:48 by mli               #+#    #+#             */
/*   Updated: 2020/06/19 18:59:04 by mli              ###   ########.fr       */
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
		ret = cd_special("HOME", env);
	else if (!ft_strcmp("-", argv[1]))
		ret = cd_special("OLDPWD", env);
	else
		ret = ft_chdir(argv[1], env);
	if (ret == 0)
		control->quit = 1;
	else if (errno)
	{
		ft_perror(argv[0], argv[1], strerror(errno));
		errno = 0;
	}
	control->exit_status = (ret == 1 ? 0 : 1);
	return (ret == 0 ? 0 : 1);
}

/*
** note : It treats special cases :
**	- cd    => go to $HOME
**	- cd -  => go to $OLDWPD
**	Prints an error if the env variable is not set
*/

int		cd_special(char *envdir, t_list *env)
{
	char *dir;

	if (!(dir = env_get(envdir, ft_strlen(envdir), env)))
	{
		ft_perror("cd", envdir, "environment variable not set");
		return (-1);
	}
	return (ft_chdir(dir, env));
}

/*
** note : Here these variables pointers are filled
**	- update_old == upold
**	- update_pwd == uppwd
**	- pwd_env == pwdptr
**		Then the OLDPWD is updated if needed
**		Doing a ft_swap in order to avoid a potential allocation
**
** RETURN:	1 on success
**			0 if an error occured
*/

int		ft_update_oldpwd(int *upold, int *uppwd, char ***pwdptr, t_list *env)
{
	char	**oldpwd;

	*pwdptr = env_get_addr("PWD", 3, env);
	oldpwd = env_get_addr("OLDPWD", 6, env);
	*uppwd = (*pwdptr != NULL);
	if ((*upold = (oldpwd != NULL)) == 0)
		return (1);
	if (*pwdptr)
		ft_ptrswap((void **)*pwdptr, (void **)oldpwd);
	if (ft_getcwd(oldpwd) == 0)
		return (0);
	return (1);
}

/*
** note : Here the directory change is performed
**		It first fills some variables :
**	- update_old => do we need to update OLDPWD
**	- update_pwd => do we need to update PWD
**	- pwd_env => the result of env_get_addr(PWD) [so no need to re-run this fct]
**		Then the OLDPWD is updated in a sub-funct if needed
**		The chdir is performed
**		Finally, the PWD is updated if needed
**
** RETURN:	1 on success
**			0 if an error occured (malloc)
**			-1 if an error occured (chdir)
*/

int		ft_chdir(char *target_dir, t_list *env)
{
	char	**pwd_env;
	int		update_pwd;
	int		update_old;

	if (ft_update_oldpwd(&update_old, &update_pwd, &pwd_env, env) == 0)
		return (0);
	printf("Moving to \033[0;1;94m%s\033[0m\n", target_dir);
	if (chdir(target_dir) == -1)
		return (-1);
	if (update_pwd && ft_getcwd(pwd_env) == 0)
		return (0);
	return (1);
}
