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
	control->term->cursor_saved = control->term->cursor;
	if (control->term->cursor.y > control->term->cursor_start.y)
	{
		if (control->term->inline_position < control->term->size_window.x)
		{
			control->term->cursor.x = control->term->cursor_start.x;
			read_process_control_combo(control, CTRL_A_COMBO);
		}
		else
		{
			terminfo_cursor_move(control, control->term->cursor.x, \
						control->term->cursor.y - 1);
			control->term->inline_position -= control->term->size_window.x;
		}
		control->term->cursor.y = control->term->cursor_saved.y - 1;
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

	control->term->cursor_saved = control->term->cursor;
	cursor_end.x = (control->term->cursor_start.x \
			+ control->term->line_len) % control->term->size_window.x;
	cursor_end.y = control->term->cursor_start.y \
			+ ((control->term->line_len + control->term->prompt_len) \
					/ control->term->size_window.x);
	if (control->term->cursor.y < cursor_end.y)
	{
		if ((control->term->cursor.y == cursor_end.y - 1) \
				&& (control->term->cursor.x > cursor_end.x))
		{
			read_process_control_combo(control, CTRL_E_COMBO);
			control->term->cursor.x = cursor_end.x;
		}
		else
		{
			terminfo_cursor_move(control, control->term->cursor.x, \
						control->term->cursor.y + 1);
			control->term->inline_position += control->term->size_window.x;
		}
		control->term->cursor.y = control->term->cursor_saved.y + 1;
	}
}

/*
** note:	This function is in charge of keeping track of the cursor's
**			position
** note:	One case when the cursor realistically needs to be replaced: when
**			writting on the last collumn (it needs to be replaced on the next
**			line.)
** note:	If when replacing the cursor on the next line we hit the bottom,
**			we need to shift the screen up.
** input:	- control struct
**			- add:	1 adding to the abscisse
**					0 substracting
**
** RETURN:	1 ok
**			0 failed.
*/

int	terminfo_cursor_track_position(t_control *control, int add)
{
	if (add)
	{
		control->term->cursor.x++;
		if (control->term->cursor.x == control->term->size_window.x)
		{
			control->term->cursor.x = 0;
			if (!terminfo_cursor_move_diagonally(control, 0))
				return (0);
			if (control->term->cursor.y + 1 != control->term->size_window.y)
				control->term->cursor.y++;
		}
	}
	else
	{
		if (control->term->cursor.x == 0)
		{
			if (!terminfo_cursor_move_diagonally(control, 1))
				return (0);
			control->term->cursor.x = control->term->size_window.x - 1;
			control->term->cursor.y--;
		}
		else
			control->term->cursor.x--;
	}
	return (1);
}
