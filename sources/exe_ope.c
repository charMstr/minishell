#include "minishell.h"

int		exe_and(t_btree *ast, t_control *control)
{
	exe_root(ast->left, control);
	if (control->exit_status == 0)
		exe_root(ast->right, control);
	return (control->exit_status);
}

int		exe_or(t_btree *ast, t_control *control)
{
	exe_root(ast->left, control);
	if (control->exit_status != 0 && !control->quit)
		exe_root(ast->right, control);
	return (control->exit_status);
}

int		exe_semi(t_btree *ast, t_control *control)
{
	exe_root(ast->left, control);
	if (ast->right && !control->quit)
		exe_root(ast->right, control);
	return (control->exit_status);
}

int		exe_cmd(t_btree *ast, t_control *control)
{
	if (!exe_simple_cmd_root((t_token *)ast->item, control))
		return (0);
	return (1);
}

int		exe_subshell(t_btree *ast, t_control *control)
{
	pid_t	pid;
	int		status;

	ft_fork(&pid);
	if (pid == 0)
	{
		exe_root(ast->left, control);
		exit(control->exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		control->exit_status = (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
	}
	return (control->exit_status);
}
