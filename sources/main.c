#include "minishell.h"

/*
** note:	this function is the master loop of the minishell
** note:	if we exit this function it means we exit the shell.
**
** RETURN:	the exit_status, that was stored int the control->exit_status field
*/

int	master_loop(t_control *control)
{
	//t_tokens_list *tokens_list;
	while (1)
	{
		input_root(control);
		if (control->quit)
			break;
		//here we should enter the parsing
		//here we should enter the command processing
		//here we should set the exit_status.
	}
	return (control->exit_status);
}

int main()
{
	struct termios	saved_copy;
	int				exit_status;
	t_control		control;

	control_init_struct(&control);
	if (!(control.term = terminfo_init_database()))
		return (1);
	if (!(termios_enable_raw_mode(&saved_copy)))
	{
		terminfo_free_struct(control.term);
		return (1);
	}
	exit_status = master_loop(&control);
	control_free_struct(&control);
	terminfo_reset_terminal();
	termios_reset_cooked_mode(&saved_copy);
    return exit_status;
}
