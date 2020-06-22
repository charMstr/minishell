#include "minishell.h"

int g_sig;

/*
** This function creates the (char **env) for the fork
** RETURN : NULL if empty, or error (control->quit raised)
*/

char	**build_env2d(t_list *env, t_control *control)
{
	int			i;
	const int	lstsize = ft_lstsize(env);
	char		**res;
	t_env		*tmp;

	if (!(res = (char **)ft_memalloc(sizeof(char *) * (lstsize + 1))))
	{
		control->quit = 1;
		return (NULL);
	}
	i = -1;
	while (env)
	{
		tmp = env->content;
		if (!(res[++i] = ft_strjoin_free(tmp->label, (char [2]){'=', '\0'}, 0))
		|| !(res[i] = ft_strjoin_free(res[i], tmp->value, 1)))
		{
			control->quit = 1;
			ft_array_free(res, lstsize);
			return (NULL);
		}
		env = env->next;
	}
	return (res);
}

/*
** Note : Do the fork, (build char **env just before)
**        + Get the exit status of the child
** RETURN : For now, always returns 1
*/

int		exe_binary_fork(char *prog, char **argv, t_control *control)
{
	char	**env;
	pid_t	pid;
	int		status;

	ft_fork(&pid);
	if (pid == 0)
	{
		if (!(env = build_env2d(control->env, control)) && control->quit)
			ft_exit("malloc", NULL, strerror(errno), 1);
		if (execve(prog, argv, env) == -1)
			ft_perror(prog, NULL, strerror(errno));
		ft_array_free(env, ft_array_len(env));
		ft_errno_exit();
	}
	else
	{
		waitpid(pid, &status, 0);
		control->exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : g_sig;
		printf("Exit status of the child was %d\n", control->exit_status);
	}
	return (1);
}

/*
** Note : Just make argv[0] in a good format if path given:
**        a.out instead of ./a.out (in argv[0])
** RETURN : 1 on Success
**          0 The path isn't given
**         -1 Malloc error -> control->quit
*/

int		exe_given_path(char **argv0, t_control *control, char **path_to_binary)
{
	char *new;

	if (!(new = ft_strrchr(*argv0, '/')))
		return (0);
	if (!(new = ft_strdup(new + 1)))
	{
		control->quit = 1;
		return (-1);
	}
	*path_to_binary = *argv0;
	*argv0 = new;
	return (1);
}

/*
** Note : Search the correct path inside $PATH : i.e. a regular file
**        (don't check rights, execve does)
** RETURN : 1 on success
**          0 not found
**         -1 malloc error
*/

int		exe_search_path(char *argv0, t_control *control, char **path_to_binary)
{
	int			i;
	int			ret;
	char		*path;
	char		**split;
	struct stat	buf;

	if (!(split = ft_split(env_get("PATH", 4, control->env), ':')))
		return (errno ? -1 : 0);
	i = -1;
	ret = 0;
	while (ret == 0 && split[++i])
	{
		if (!(path = ft_strjoin(split[i], argv0)))
			ret = -1;
		else if (!stat(path, &buf) && S_ISREG(buf.st_mode))
		{
			*path_to_binary = path;
			ret = 1;
		}
		else
			ft_free((void **)&path);
	}
	ft_array_free(split, ft_array_len(split));
	return (ret);
}

/*
** Note : The root function for executing binaries
**       First, check if the argv[0] contains a '/'.
**           If yes, don't need to check the content of $PATH
**           If no, check it
**              If failed, command not found
**       Finally, do the fork
**
** RETURN : 1 on success
**          0 not found
**         -1 malloc error, thus, control->quit is raised
*/

int		exe_binary(t_simple_cmd *cmd, t_control *control)
{
	int		ret;
	char	*argv0;
	char	*path_to_binary;

	g_sig = 1;
	path_to_binary = NULL;
	if ((ret = exe_given_path(&cmd->argv[0], control, &path_to_binary)) == -1)
		return (ret);
	else if (ret == 0)
	{
		if (!(argv0 = ft_strjoin((char []){'/', '\0'}, cmd->argv[0])) ||
			((ret = exe_search_path(argv0, control, &path_to_binary)) == -1))
			control->quit = 1;
		else if (ret == 0 && (control->exit_status = 127))
			ft_perror(cmd->argv[0], NULL, "Command not found");
		free(argv0);
		if (ret != 1)
			return (ret);
	}
	ret = exe_binary_fork(path_to_binary, cmd->argv, control);
	free(path_to_binary);
	return (ret);
}
