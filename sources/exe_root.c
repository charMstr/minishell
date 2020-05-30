#include "minishell.h"

/*
** this file is the root file for the execution of the minishell commands. The
** start point is the ast, a binary tree whose nodes->item are tokens.
*/

/*
// update me later!!!
** note:	this function will be the starting point for interpreting the ast.
**
** for now it will just parcour the ast and look for simple commands.
*/

void	exe_root(t_btree *ast, t_control *control)
{
	printf("\033[36mENTERING THE EXE_ROOT FUNC\033[0m\n");
	if (!exe_prototype(control, ast))
		return ;
}

int	exe_prototype(t_control *control, t_btree *ast)
{
	if (!ast)
		return (0);
	exe_prototype(control, ast->left);
	exe_prototype(control, ast->right);
	if (btree_id(ast) == LIST)
	{
		if (!exe_simple_cmd_root((t_token*)ast->item, control))
			return (0);
	}
	// need to modify the returns etc so that we quit if there is a problem...
	// need to organise the pipes sequence, but for now we can exe a simple cmd
	return (1);
}
