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
** and handles ||, &&, ;
*/

const t_exe *g_exec = (const t_exe []){{AND_IF, exe_and}, {OR_IF, exe_or},
	{PIPE, exe_pipe}, {LIST, exe_cmd}, {SEMI, exe_semi}, {-1, exe_semi},
	{0, NULL}};

void	exe_root(t_btree *ast, t_control *control)
{
	int i;
	int current_id;

//	printf("\033[36mENTERING THE EXE_ROOT FUNC\033[0m\n");
	if (!ast || control->quit)
		return ;
	i = 0;
	current_id = btree_id(ast);
	while (g_exec[i].fct != NULL && g_exec[i].id != current_id)
		i++;
	if (g_exec[i].fct)
		g_exec[i].fct(ast, control);
}
