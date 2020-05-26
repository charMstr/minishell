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
	control->quit = 0;
	control->ctrl_c = 0;
	control->exit_status = 0;
	control->history = NULL;
	control->term = NULL;
	control->env = NULL;
	ft_bzero((void*)(&control->lexer_end), sizeof(t_lexer_end));
}

/*
** note:	this function is in charge of cleaning everything that was malloced
**			from the stuct, bt not the struct itself.
*/

void	control_free_struct(t_control *control)
{
	terminfo_free_struct(control->term);
	ft_dlstclear(&(control->history->head), history_del_content);
	ft_lstclear(&control->env, env_del_struct);
}
