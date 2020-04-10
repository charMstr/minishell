#include "minishell.h"

/*
** this file will take care of the ctrl + LETTER combinaision recorded.
** note:	ctrl_c and ctrl_D are intercepted before this function call
*/

/*
** note:	this is the root function for adding special features when the user
**			uses a ctrl + letter combinaison.
** note:	the flags like control->quit wil have to be raised in case of error
*/

void	read_process_control_combo(t_control *control, char c)
{
	if (c == CTRL_A_COMBO)
	{
		if (!terminfo_cursor_move_endl(control, 1))
			return ;
		control->term->inline_position = -1;
	}
	else if (c == CTRL_E_COMBO)
	{
		if (!terminfo_cursor_move_endl(control, 0))
			return ;
		control->term->inline_position = control->term->line_len -1;
	}
}
