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

int		exe_is_builtin(char *argv0);
void	exe_prototype(t_control *control, t_btree *ast);
void	exe_call_builtin(t_simple_cmd *cmd, int id, t_control *control);

void	exe_root(t_btree *ast, t_control *control)
{
	(void)control;
	printf("\033[36mENTERING THE EXE_ROOT FUNC\033[0m\n");
	if (!simple_cmd_convert_root(ast))
	{
		control->quit = 1;
		return ;
	}
	exe_prototype(control, ast);
}

void	exe_prototype(t_control *control, t_btree *ast)
{
	t_token *tok;
	int		builtin;

	if (!ast)
		return ;
	exe_prototype(control, ast->left);
	exe_prototype(control, ast->right);
	if (btree_id(ast) == CMD)
	{
		tok = (t_token*)ast->item;
		debug_simple_cmd(((t_simple_cmd *)tok->str));
		if ((builtin = exe_is_builtin(((t_simple_cmd *)tok->str)->argv[0])))
		{
			exe_call_builtin(((t_simple_cmd *)tok->str), builtin, control);
			printf("this is a builtin\n");
		}
	}
}

/*
** note:	This function is in charge of calling the right builtin.
** note:	Failure can occure because some builin like set use malloc.
** input:	id is the builin id, see typedef in .h
**			control struct
**
** RETURN:	1 OK
**			0 KO.
*/

void	exe_call_builtin(t_simple_cmd *cmd, int id, t_control *control)
{
	if (id == B_ECHO)
		//need in echo to make it use the redirections. and need to modify its
		//general behavior regarding the \\, \t etc (quoted or not)
		echo_builtin(cmd->argv);
	(void)control;
}

/*
** note:	this function will have to tell us if the command to run is a
**			builtin or not.
**
** return:	builtin number
**			0 other.
*/

int	exe_is_builtin(char *argv0) //OK
{
	if (!argv0)
		return (0);
	if (!ft_strcmp(argv0, "echo"))
		return (B_ECHO);
	else if (!ft_strcmp(argv0, "cd"))
		return (B_CD);
	else if (!ft_strcmp(argv0, "pwd"))
		return (B_PWD);
	else if (!ft_strcmp(argv0, "export"))
		return (B_EXPORT);
	else if (!ft_strcmp(argv0, "unset"))
		return (B_UNSET);
	else if (!ft_strcmp(argv0, "env"))
		return (B_ENV);
	else if (!ft_strcmp(argv0, "exit"))
		return (B_EXIT);
	else
		return (0);
}
