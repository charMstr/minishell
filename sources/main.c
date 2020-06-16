#include "minishell.h"

/*
** note:	this function is the master loop of the minishell
** note:	if we exit this function it means we exit the shell.
**
** RETURN:	the exit_status, that was stored int the control->exit_status field
*/

extern char **environ;

int	master_loop(t_control *control)
{
	t_list *tokens_list;
	t_btree *ast;

	if (!(control->env = env_build_linked_list(environ)))
		return (1);
	while (1)
	{
		tokens_list = input_root(control);
		if (control->quit)
			break;
		if (control->ctrl_c || control->lexer_end.unexpected)
			continue;
		//here we should enter the parsing
		ast = parser_root(tokens_list, control);
		if (control->quit)
			break;
		//here we should enter the command processing
		exe_root(ast, control);
		btree_clear(&ast, del_token);
		if (control->quit)
			break;
		//here we should set the exit_status.
	}
	return (control->exit_status);
}

int main(void)
{
	struct termios	saved_copy;
	int				exit_status;
	t_control		control;

	if (!control_init_struct(&control) ||
		!(termios_enable_raw_mode(&saved_copy)))
	{
		ft_print_error("minishell", NULL,
				(errno ? strerror(errno) : "Couldn't init minishell"));
		control_free_struct(&control);
		return (1);
	}
	exit_status = master_loop(&control);
	control_free_struct(&control);
	terminfo_reset_terminal();
	termios_reset_cooked_mode(&saved_copy);
    return (exit_status);
}
