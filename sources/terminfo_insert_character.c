#include "minishell.h"

/*
** this file is in charge of inserting to the screen the charcter, and
** especially the lines if we are in a multiline situation.
*/

/*
** note:	this function is the base for inserting a character in the screen
**
** RETURN:	1 ok
**			0 failure
*/

int	terminfo_insert_char(t_control *control, char c)
{
	//need to change this functions so that it can insert INLINE
	//	and SHIFT as well if characters are pushed at the end of the line(s).
	if (!terminfo_cursor_get_pos(control))
		return (0);
	if (control->term->cursor.x == control->term->size_window.x)
	{
		write(1, &c, 1);
		if (!terminfo_cursor_move_diagonally(control, 0))
			return (0);
	}
	else
		write(1, &c, 1);
	return (1);
}
