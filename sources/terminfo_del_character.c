#include "minishell.h"

/*
** this file takes care of erasing a character from the screen.
*/

/*
** note:	this function will erase a character.
**
** note:	if we are in the middle of the lime we will have to update line
**			accordingly.
**
** RETURN:	1 0k
**			0 failure
*/

int		terminfo_del_char(t_control *control)
{
	if (!terminfo_del_and_move(control))
		return (0);
	if (!terminfo_cursor_track_position(control, 0))
		return (0);
	if (!terminfo_del_char_cascade(control))
		return (0);
	return (1);
}

/*
** note:	this function will take care of deleting a character in place.
** note:	the virtual position will be updated right after this function call
**
** RETURN:	1 ok
**			0 failure
*/

int		terminfo_del_and_move(t_control *control)
{
	char *caps;

	if (control->term->cursor.x)
	{
		if (!(caps = terminfo_get_caps("cub1", control)))
			return (0);
		tputs(caps, 1, ft_putchar);
		if (!terminfo_del_in_place(control))
			return (0);
	}
	else
	{
		if (!terminfo_cursor_move_diagonally(control, 1))
			return (0);
		if (!(caps = terminfo_edit_caps(control, "ech", 1)))
			return (0);
		tputs(caps, 1, ft_putchar);
	}
	return (1);
}

/*
** note:	this function will simply delecte a character in place
**
** RETURN:	1 ok
**			0 failure
*/

int		terminfo_del_in_place(t_control *control)
{
	char *caps;

	if (!(caps = terminfo_edit_caps(control, "dch1", 1)))
		return (0);
	tputs(caps, 1, ft_putchar);
	return (1);
}


/*
** note:	This function will check if the deleteion of the character in the
**			display needs a shift to the left and up of the following lines.
**			If so, the characters are inserted at the end of the line, and
**			deleted at the begining of next line in cascade.
**
** note:	the character at this stage has been inserted, and term->len_line,
**			and term->inline_position have not been updated yet (--).
**
** return:	1 ok
**			0 failure
*/

int	terminfo_del_char_cascade(t_control *control)
{
	int		bottom_y;
	char	c;
	int		index_char_to_reprint;

	control->term->cursor_saved = control->term->cursor;
	bottom_y = control->term->cursor_start.y + ((control->term->line_len - 1\
				+ control->term->prompt_len) / control->term->size_window.x);
	index_char_to_reprint = terminfo_del_get_index_for_cascade(control);
	while (control->term->cursor.y < bottom_y)
	{
		c = control->term->line[index_char_to_reprint];
		terminfo_del_char_cascade_assist(control, c);
		index_char_to_reprint += control->term->size_window.x;
	}
	if (!(terminfo_cursor_saved_reset(control)))
		return (0);
	return (1);
}

/*
** note:	this function is created for the sake of readability, it will
**			simply find the index of the first char to needs to be reprinted at
**			the end of the line while cascading the deletion. The next index
**			are simply found adding the width of the window.
**
** return:	index of the character we need to make reappear at the end of line.
*/

int	terminfo_del_get_index_for_cascade(t_control *control)
{
	int current;
	int	offset;

	current = control->term->prompt_len + control->term->inline_position - 1;
	offset = control->term->size_window.x - \
			 (current % control->term->size_window.x);
	return (control->term->inline_position - 1 + offset);
}

/*
** note:	this function will always do the same operation: set the cursor to
**			the endl of the current line, insert in place the given char, then
**			move (and update) the cursor to the beginning of the next line, and
**			do a delete in place (including shifting the line to the left).
** RETURN:	1 ok
**			0 failure
*/

int	terminfo_del_char_cascade_assist(t_control *control, char c)
{
	t_int_pair *cursor;

	cursor = &(control->term->cursor);
	cursor->x = control->term->size_window.x - 1;
	if (!terminfo_cursor_move(control, cursor->x, cursor->y))
		return (0);
	if (!terminfo_insert_in_place(control, c))
		return (0);
	cursor->y += 1;
	cursor->x = 0;
	if (!terminfo_cursor_move(control, cursor->x, cursor->y))
		return (0);
	if (!terminfo_del_in_place(control))
		return (0);
	return (1);
}
