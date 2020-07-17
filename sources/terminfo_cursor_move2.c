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

void	terminfo_cursor_move_up(t_control *control, t_int_pair *cursor)
{
	t_int_pair	previous_end;

	if (cursor->y <= control->term->cursor_start.y)
		return ;
	previous_end = terminfo_predict_previous_line_cursor_end(control);
	if (cursor->y == control->term->cursor_start.y + 1 \
			&& cursor->x < control->term->prompt_len)
		read_process_control_combo(control, CTRL_A_COMBO);
	else if (cursor->x > previous_end.x)
	{
		terminfo_cursor_move(control, previous_end.x, previous_end.y);
		control->term->inline_position -= cursor->x + 1;
		*cursor = previous_end;
	}
	else
	{
		terminfo_cursor_move(control, cursor->x, cursor->y - 1);
		control->term->inline_position -= cursor->x \
										+ (previous_end.x - cursor->x) + 1;
		cursor->y--;
	}
}

/*
** note:	This function will take care of moving the cursor down if possible.
**			We cant go lower than the last line cursor position.
** note:	It will update accordingly the control->term->inline_position.
**
** note:	As always if a problem occured the control->quit flag is raised.
*/

void	terminfo_cursor_move_down(t_control *control, t_int_pair *cursor)
{
	t_int_pair	cursor_end;
	int			len_next;
	int			current_len;

	len_next = terminfo_predict_next_line_len(control);
	cursor_end = terminfo_cursor_get_endl(control);
	current_len = terminfo_predict_current_line_len(control);
	if (cursor->y >= cursor_end.y)
		return ;
	if (cursor->x >= len_next - 1)
	{
		cursor->y++;
		if (cursor->y == cursor_end.y && cursor->x >= len_next)
			len_next++;
		terminfo_cursor_move(control, len_next - 1, cursor->y);
		control->term->inline_position += current_len - cursor->x \
											+ len_next - 1;
		cursor->x = len_next - 1;
	}
	else
	{
		terminfo_cursor_move(control, cursor->x, ++(cursor->y));
		control->term->inline_position += current_len;
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
		if (control->term->cursor.x + 1 == control->term->size_window.x)
		{
			if (!terminfo_cursor_move_diagonally_down(control))
				return (0);
		}
		else
			control->term->cursor.x++;
	}
	else
	{
		if (control->term->cursor.x == 0)
		{
			if (!terminfo_cursor_move_diagonally_up(control))
				return (0);
		}
		else
			control->term->cursor.x--;
	}
	return (1);
}

/*
** note:	this function will position the cursor at the beginning or the end
**			of the current line.
** input:	- start: 1 for start, 0 for end
**			- control struct
**
** RETURN:	1 ok
**			0 failure
*/

int			terminfo_cursor_move_endl(t_control *control, int start)
{
	t_int_pair cursor_end;

	if (start)
	{
		if(!terminfo_cursor_move(control, control->term->cursor_start.x, \
					control->term->cursor_start.y))
			return (0);
		control->term->cursor = control->term->cursor_start;
	}
	else
	{
		cursor_end = terminfo_cursor_get_endl(control);
		if (!terminfo_cursor_move(control, cursor_end.x, cursor_end.y))
			return (0);
		control->term->cursor = cursor_end;
	}
	return (1);
}
