#include "minishell.h"

int		exe_pipe2(t_btree *ast, t_control *control)
{
	int fildes[2];

	ft_pipe(&fildes);
	return (control->exit_status);
	(void)ast;
}

int		exe_pipe(t_btree *ast, t_control *control)
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) == 0)
	{
		exe_pipe2(ast, control);
		exit(control->exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		control->exit_status = (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
	}
	return (control->exit_status);
}
