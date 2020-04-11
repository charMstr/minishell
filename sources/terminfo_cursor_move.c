#include "minishell.h"

/*
** this file takes care of the cursor motions.
*/

/*
** note:	this function will move the cursor to the right if possible
*/

void	terminfo_cursor_move_right(t_control *control)
{
	char *caps;

	if (control->term->inline_position + 1 < control->term->line_len)
	{
		if (control->term->cursor.x + 1 == control->term->size_window.x)
		{
			control->term->cursor.x = 0;
			control->term->cursor.y++;
			if (!(caps = terminfo_get_caps("ind", control)))
				return ;
		}
		else
		{
			control->term->cursor.x++;
			if (!(caps = terminfo_get_caps("cuf1", control)))
				return ;
		}
		tputs(caps, 1, ft_putchar);
		control->term->inline_position++;
	}
}

/*
** note:	this function will move the cursor to the left if possible
*/

void	terminfo_cursor_move_left(t_control *control)
{
	char *caps;

	if (control->term->inline_position >= 0)
	{
		if (control->term->cursor.x == 0)
		{
			if (!terminfo_cursor_move_diagonally(control, 1))
				return ;
			control->term->cursor.x = control->term->size_window.x - 1;
			control->term->cursor.y--;
		}
		else
		{
			if (!(caps = terminfo_get_caps("cub1", control)))
				return ;
			tputs(caps, 1, ft_putchar);
			control->term->cursor.x--;
		}
		control->term->inline_position--;
	}
}


/*
** note:	this function just calls terminfo_cursor_move() to make a
**			move diagonally.
** input:	- diag:	1 for going up and right
**					0 for down and left
**			- control struct
**
** RETURN:	1 ok
**			0 failed
*/

int	terminfo_cursor_move_diagonally(t_control *control, int diag)
{
	char *caps;

	if (diag == 1)
	{
		if (!terminfo_cursor_move(control, control->term->size_window.x - 1, \
					control->term->cursor.y - 1))
			return (0);
		return (1);
	}
	else
	{
		if (control->term->cursor.y + 1 == control->term->size_window.y)
		{
			if (!(caps = terminfo_edit_caps(control, "indn", 1)))
				return (0);
			control->term->cursor_start.y--;
			control->term->cursor_saved.y--;
			tputs(caps, 1, ft_putchar);
		}
		if (!terminfo_cursor_move(control, 0, control->term->cursor.y + 1))
			return (0);
		return (1);
	}
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
		cursor_end.x = (control->term->cursor_start.x \
				+ control->term->line_len) % control->term->size_window.x;
		cursor_end.y = control->term->cursor_start.y \
				+ ((control->term->line_len + control->term->prompt_len) \
						/ control->term->size_window.x);
		if (!terminfo_cursor_move(control, cursor_end.x, cursor_end.y))
			return (0);
		control->term->cursor = cursor_end;
	}
	return (1);
}
