#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

char	*build_env2d_line(t_env *env)
{
	char *res;

	if (!(res = ft_strjoin_free(env->label, (char [2]){'=', '\0'}, 0)))
		return (NULL);
	if (!(res = ft_strjoin_free(res, env->value, 1)))
		return (NULL);
	return (res);
}

char	**build_env2d(t_list *env, t_control *control)
{
	int		i;
	int		lstsize;
	char	**res;

	if ((lstsize = ft_lstsize(env)) < 1)
		return (NULL);
	if (!(res = (char **)ft_memalloc(sizeof(char *) * (lstsize + 1))))
	{
		control->quit = 1;
		return (NULL);
	}
	i = -1;
	while (env)
	{
		if (!(res[++i] = build_env2d_line(env->content)))
		{
			control->quit = 1;
			ft_array_free(res, lstsize);
			return (NULL);
		}
		env = env->next;
	}
	return (res);
}

int		is_binary(struct stat buf)
{
	// Check if it's a regular file + one of the exec rights
	// But may be an useless function
	if (S_ISREG(buf.st_mode) && (buf.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
		return (1);
	return (0);
}

int		exe_binary_fork(char *prog, char **argv, t_control *control)
{
	char	**env;
	pid_t	pid;
	int		status;

	if ((pid = fork()) == 0)
	{
		if (!(env = build_env2d(control->env, control)))
			return (-1);
		if (execve(prog, argv, env) == -1)
			ft_print_error(prog, NULL, strerror(errno));
		ft_array_free(env, ft_array_len(env));
		control->exit_status = 1;
		control->quit = 1;
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		control->exit_status = (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
		printf("Exit status of the child was %d\n", control->exit_status);
	}
	return (1);
}

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
** Note : Search the correct path with $PATH
**
** RETURN : 1 on success
**          0 not found
**         -1 malloc error
*/

int		exe_search_path(char *argv0, t_control *control, char **path_to_binary)
{
	int			i;
	char		*path;
	char		**split;
	struct stat	buf;

	if (!(split = ft_split(env_get("PATH", 4, control->env), ':')))
		return (errno ? -1 : 0);
	i = -1;
	while (split[++i])
	{
		if (!(path = ft_strjoin(split[i], argv0)))
		{
			ft_array_free(split, ft_array_len(split));
			return (-1);
		}
		if (!stat(path, &buf) && S_ISREG(buf.st_mode))
		{
			*path_to_binary = path;
			ft_array_free(split, ft_array_len(split));
			return (1);
		}
		ft_free((void **)&path);
	}
	ft_array_free(split, ft_array_len(split));
	return (0);
}

int		exe_binary(t_simple_cmd *cmd, t_control *control)
{
	int		ret;
	char	*argv0;
	char	*path_to_binary;

	printf("\e[95mThis is a binary !\e[0m\n");
	path_to_binary = NULL;
	if ((ret = exe_given_path(&cmd->argv[0], control, &path_to_binary)) == -1)
		return (ret);
	else if (ret == 0)
	{
		// search true path to binary
		ret = 0;
		if ((argv0 = ft_strjoin((char []){'/', '\0'}, cmd->argv[0])) &&
			((ret = exe_search_path(argv0, control, &path_to_binary)) == -1))
			control->quit = 1;
		else if (ret == 0)
			ft_print_error(cmd->argv[0], NULL, "Command not found");
		free(argv0);
		if (ret != 1)
			return (ret);
	}
	ret = exe_binary_fork(path_to_binary, cmd->argv, control);
	free(path_to_binary);
	return (ret);
}
