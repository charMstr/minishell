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
	if (control->exit_status != 0)
		exe_root(ast->right, control);
	return (control->exit_status);
}

int		exe_pipe(t_btree *ast, t_control *control)
{
	printf("EXE_PIPE : |\n");
	return (control->exit_status);
	(void)ast; (void)control;
}

int		exe_semi(t_btree *ast, t_control *control)
{
	exe_root(ast->left, control);
	if (ast->right)
		exe_root(ast->right, control);
	return (control->exit_status);
}

int		exe_cmd(t_btree *ast, t_control *control)
{
	if (!exe_simple_cmd_root((t_token *)ast->item, control))
		return (0);
	return (1);
}
