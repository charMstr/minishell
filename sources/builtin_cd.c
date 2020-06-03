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
**			0 if an error occured (malloc)
**			-1 if an error occured (chdir)
*/

int		ft_print_error(char *str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
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
		ft_putstr_fd("\033[0;1;91mminishell: cd: ", 1);
		ft_putstr_fd(envdir, 1);
		ft_putstr_fd(" not set\033[0m\n", 1);
		return (0);
	}
	return (ft_chdir(dir, env));
}

/*
** note : This is the cd main fonction
*/

int		cd_builtin(t_list *env, char **argv, t_control *control)
{
	int ret;

	if (!argv[1])
		ret = cd_special("HOME", env);
	else if (!ft_strcmp("-", argv[1]))
		ret = cd_special("OLDPWD", env);
	else
		ret = ft_chdir(argv[1], env);
	if (ret == 1)
		ft_ls(".", 0);
	else if (ret == 0)
		control->quit = 1;
	else
	{
		ft_print_error(strerror(errno));
		errno = 0;
	}
	control->exit_status = (ret == 1 ? 0 : 1);
	return (ret == 0 ? 0 : 1);
}
