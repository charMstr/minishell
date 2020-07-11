#include "minishell.h"

/*
** note:	this function is the master loop of the minishell
** note:	if we exit this function it means we exit the shell.
**
** RETURN:	the exit_status, that was stored int the control->exit_status field
*/

int	master_loop(t_control *control)
{
	t_list	*tokens_list;
	t_btree	*ast;

	while (!control->quit)
	{
		if (!termios_enable_raw_mode(control, &control->termios_default))
			break ;
		tokens_list = input_root(control);
		if (!termios_reset_cooked_mode(control, &control->termios_default))
			break ;
		if (control->quit || control->ctrl_c || control->lexer_end.unexpected)
			continue;
		ast = parser_root(tokens_list, control);
		if (control->quit)
			break;
		exe_root(ast, control);
		btree_clear(&ast, del_token);
	}
	return (control->exit_status);
}

int main(void)
{
	int				exit_status;
	t_control		control;

	signal(SIGQUIT, ft_sigquit);
	signal(SIGINT, ft_sigint);
	if (!control_init_struct(&control) ||
		!(termios_enable_raw_mode(&control, &control.termios_default)))
	{
		ft_perror(NULL, NULL, errno ? strerror(errno) : "Couldn't initialize");
		control_free_struct(&control);
		return (1);
	}
	exit_status = master_loop(&control);
	control_free_struct(&control);
	terminfo_reset_terminal();
	termios_reset_cooked_mode(&control, &control.termios_default);
    return (exit_status);
}
