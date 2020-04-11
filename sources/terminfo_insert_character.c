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
	if (!terminfo_insert_in_place(control, c))
		return (0);
	if (!(terminfo_cursor_track_position(control, 1)))
		return (0);
	if (!terminfo_insert_char_cascade(control))
		return (0);
	return (1);
}

/*
** note:	this function is in charge of inserting in the screen the given
**			char, in place.
**
** RETURN:	1 ok
**			0 failure
*/

int terminfo_insert_in_place(t_control *control, char c)
{
	char *caps;

	if (!(caps = terminfo_edit_caps(control, "ich", 1)))
		return (0);
	tputs(caps, 1, ft_putchar);
	ft_putchar_fd(c, 1);
	return (1);
}

/*
** note:	This function will check if the insertion of the character in the
**			display shifts the last character of the line outside of the
**			screen. If so, the characters are inserted at the beginning of the
**			next line in cascade.
**
** note:	the character at this stage has been inserted, and term->len_line,
**			and term->inline_position have been updated (++).
**
** return:	1 ok
**			0 failure
*/

//needs to be fixed..
int	terminfo_insert_char_cascade(t_control *control)
{
	int current;
	int	tt_len;
	int	offset;
	char c;

	control->term->cursor_saved = control->term->cursor;
	current = control->term->prompt_len + control->term->inline_position;
	offset = control->term->size_window.x - \
			 (current % control->term->size_window.x);
	tt_len = control->term->prompt_len + control->term->line_len;
	while (current + offset < tt_len)
	{
		if (control->term->cursor.x != 0)
			if (!(terminfo_cursor_move_diagonally(control, 0)))
				return (0);
		control->term->cursor.y++;
		c = control->term->line[current - control->term->prompt_len + offset];
		if (!(terminfo_insert_in_place(control, c)))
			return (0);
		current += control->term->size_window.x;
	}
	if (!(terminfo_cursor_saved_reset(control)))
		return (0);
	return (1);
}
