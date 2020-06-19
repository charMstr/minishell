#include "minishell.h"

void	exe_pipe_child(t_btree *ast, t_control *control)
{
	t_pipe pipe;

	ft_fork_pipe(&pipe);
	if (pipe.pid != 0)
	{
		close(pipe.fildes[0]);
		if (dup2(pipe.fildes[1], STDOUT_FILENO) == -1)
			ft_exit("dup2", NULL, strerror(errno), EXIT_FAILURE);
		exe_root(ast->left, control);
		close(pipe.fildes[1]);
	}
	else
	{
		close(pipe.fildes[1]);
		if (dup2(pipe.fildes[0], STDIN_FILENO) == -1)
			ft_exit("dup2", NULL, strerror(errno), EXIT_FAILURE);
		exe_root(ast->right, control);
		close(pipe.fildes[0]);
		waitpid(pipe.pid, &pipe.status, 0);
	}
	exit(control->exit_status);
}

int		exe_pipe(t_btree *ast, t_control *control)
{
	pid_t	pid;
	int		status;

	ft_fork(&pid);
	if (pid == 0)
		exe_pipe_child(ast, control);
	else
	{
		waitpid(pid, &status, 0);
		control->exit_status = (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
	}
	return (control->exit_status);
}
