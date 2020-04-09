#include "minishell.h"
//#include "terminfo.h"

/*
** this file is in charge of the control structure that will be carried all
** along the main steps of the minishell (at least the input , lexer as a start
*/

/*
** note:	this function will init the t_control struct
*/

void	control_init_struct(t_control *control)
{
	control->term = NULL;
	control->exit_status = 0;
	control->quit = 0;
	control->first_time = 1;
	control->index_in_history = 0;
	control->ctrl_c = 0;
}

/*
** note:	this function is in charge of cleaning everything that was malloced
**			from the stuct, bt not the struct itself.
*/

void	control_free_struct(t_control *control)
{
	terminfo_free_struct(control->term);
}
