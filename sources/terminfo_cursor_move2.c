#include "minishell.h"

/*
** this file takes care of the cursor motions.
*/

/*
** note:	This function will take care of moving the cursor up if possible.
**			We cant go higher than the promt.
** note:	It will update accordingly the control->term->inline_position.
**
** note:	here if any of the functions failed. we can keep going as the flag
**			control->quit will be raised then caught getting out
*/

void	terminfo_cursor_move_up(t_control *control)
{
	if (!terminfo_cursor_get_pos(control, &(control->term->cursor)))
		return ;
	if (control->term->cursor.y > control->term->cursor_start.y)
	{
		if (control->term->inline_position < control->term->size_window.x)
			read_process_control_combo(control, CTRL_A_COMBO);
		else
		{
			terminfo_cursor_move(control, control->term->cursor.x, \
						control->term->cursor.y - 1);
			control->term->inline_position -= control->term->size_window.x;
		}
	}
}

/*
** note:	This function will take care of moving the cursor down if possible.
**			We cant go lower than the last cursor position.
** note:	It will update accordingly the control->term->inline_position.
**
** note:	As always if a problem occured the control->quit flag is raised.
*/

void	terminfo_cursor_move_down(t_control *control)
{
	t_int_pair cursor_end;

	if (!terminfo_cursor_get_pos(control, &(control->term->cursor)))
		return ;
	cursor_end.x = (control->term->cursor_start.x \
			+ control->term->line_len) % control->term->size_window.x;
	cursor_end.y = control->term->cursor_start.y \
			+ ((control->term->line_len + control->term->prompt_len) \
					/ control->term->size_window.x);
	if (control->term->cursor.y < cursor_end.y)
	{
		if ((control->term->cursor.y == cursor_end.y - 1) \
				&& (control->term->cursor.x > cursor_end.x))
			read_process_control_combo(control, CTRL_E_COMBO);
		else
		{
			terminfo_cursor_move(control, control->term->cursor.x, \
						control->term->cursor.y + 1);
			control->term->inline_position += control->term->size_window.x;
		}
	}
}
