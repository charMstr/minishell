#include "minishell.h"

/*
** this file takes care of the cursor motions.
*/

/*
** note:	this function will move the cursor to the right if possible.
**			cases for going to the next line: we havent reached the end of the
**			string, and we either reach the end of the line or a '\n'.
**
** RETURN:	1 ok
**			0, failure
*/

int	terminfo_cursor_move_right(t_control *control)
{
	char	*caps;
	int		cur_line_end_index;

	cur_line_end_index = terminfo_predict_current_line_end_index(control);
	if (control->term->inline_position + 1 >= control->term->line_len)
		return (1);
	if (control->term->inline_position + 1 == cur_line_end_index)
	{
		if (!terminfo_cursor_move_diagonally_down(control))
			return (0);
	}
	else
	{
		control->term->cursor.x++;
		if (!(caps = terminfo_get_caps("cuf1", control)))
			return (0);
		tputs(caps, 1, ft_putchar);
	}
	control->term->inline_position++;
	return (1);
}

/*
** note:	this function will move the cursor to the left if possible
**
** RETURN:	1 ok
**			0 ko
*/

int	terminfo_cursor_move_left(t_control *control)
{
	char		*caps;

	if (control->term->inline_position < 0)
		return (1);
	if (control->term->cursor.x == 0)
	{
		if (!terminfo_cursor_move_diagonally_up(control))
			return (0);
	}
	else
	{
		if (!(caps = terminfo_get_caps("cub1", control)))
			return (0);
		tputs(caps, 1, ft_putchar);
		control->term->cursor.x--;
	}
	control->term->inline_position--;
	return (1);
}

/*
** note:	this function will call terminfo_cursor_move() and place the
**			cursor at the end of the upper line. It will also update the
**			control->term->cursor.
** note:	if the cursor is already on the first line: do nothing
**
** RETURN:	1 ok
**			0 failure.
*/

int	terminfo_cursor_move_diagonally_up(t_control *control)
{
	t_int_pair	previous_end;

	if (control->term->cursor_start.y == control->term->cursor.y)
		return (1);
	previous_end = terminfo_predict_previous_line_cursor_end(control);
	if (!terminfo_cursor_move(control, previous_end.x, previous_end.y))
		return (0);
	control->term->cursor = previous_end;
	return (1);
}

/*
** note:	this function will call terminfo_cursor_move() and place the cursor
**			at the start of the next line. control->term->cursor is updatted
**			accordingly.
**
** RETURN:	1 ok
**			0 failure
*/

int	terminfo_cursor_move_diagonally_down(t_control *control)
{
	char *caps;

	if (control->term->cursor.y + 1 == control->term->size_window.y)
	{
		if (!(caps = terminfo_edit_caps(control, "indn", 1)))
			return (0);
		control->term->cursor_start.y--;
		control->term->cursor_saved.y--;
		control->term->cursor.y--;
		tputs(caps, 1, ft_putchar);
	}
	if (!terminfo_cursor_move(control, 0, control->term->cursor.y + 1))
		return (0);
	control->term->cursor.x = 0;
	control->term->cursor.y += 1;
	return (1);
}

/*
** note:	this function will move the cursor to the given position
**
** RETURN:	1 OK
**			0 failure
*/

int	terminfo_cursor_move(t_control *control, int x, int y)
{
	char *caps;

	if (!(caps = terminfo_get_caps("cup", control)))
		return (0);
	caps = tgoto(caps, x, y);
	if (!(caps + 1))
	{
		control->quit = 1;
		return (0);
	}
	tputs(caps, 1, ft_putchar);
	return (1);
}
