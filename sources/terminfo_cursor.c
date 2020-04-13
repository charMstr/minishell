#include "minishell.h"

/*
** this file take scare of the cursor related functions using the terminfo
** utility.
*/


/*
** note:	this function will set the cursor's curent position in the
**			dedicated structure (inside control->term->cursor)
**
** input:	- control struct
**			- curs:	a cursor:	it can be control->term->cursor
**								or control->term->saved_cursor ...
** RETURN:	1 ok
**			0 failure
*/

int		terminfo_cursor_get_pos(t_control *control, t_int_pair *curs)
{
	char *caps;

	if (!(caps = terminfo_get_caps("u7", control)))
		return (0);
	terminfo_cursor_get_pos_assist(caps, curs);
	//we add this here so that we dont have to do it all the time
	curs->x--;
	curs->y--;
	return (1);
}

/*
** note:	this function is in charge of yielding the position of the cursor.
**			the position is put inside control->term->cursor
**
** input:	-caps:	the caps control sequence of characters that containes the
**					current cursor's position.
**			-cursor (x anf y field will be filled).
*/

void	terminfo_cursor_get_pos_assist(char *caps, t_int_pair *cursor)
{
	int		first_coord;
	char	c;

	first_coord = 1;
	cursor->x = 0;
	cursor->y = 0;
	tputs(caps, 1, ft_putchar);
	while (read(STDIN_FILENO, &c, 1) == 1)
	{
		if (c == '\033' || c == '[')
			continue;
		if (first_coord && ft_isdigit(c))
		{
			cursor->y *= 10;
			cursor->y += c - 48;
			continue;
		}
		first_coord = 0;
		if (ft_isdigit(c))
		{
			cursor->x *= 10;
			cursor->x += c -48;
		}
		if (c == 'R')
			break;
	}
}

/*
** note:	this function will restore the cursor's position.
**
** RETURN:	1 ok
**			0 failure
*/

int		terminfo_cursor_saved_reset(t_control *control)
{
	control->term->cursor = control->term->cursor_saved;
	if(!terminfo_cursor_move(control, control->term->cursor_saved.x, \
				control->term->cursor_saved.y))
		return (0);
	return (1);
}

/*
** note:	this function will find the coordinates of the cursor when its at
**			the very end of the line.
*/

t_int_pair	terminfo_cursor_get_endl(t_control *control)
{
	t_int_pair cursor_end;

	cursor_end.x = (control->term->cursor_start.x \
			+ control->term->line_len) % control->term->size_window.x;
	cursor_end.y = control->term->cursor_start.y \
			+ ((control->term->line_len + control->term->prompt_len) \
					/ control->term->size_window.x);
	return (cursor_end);
}

/*
** note:	this function will refresh the screen from start of the line until
**			the bottom of the screen.
** note:	according to documentation, to use "ed" we need to be place on the
**			index ZERO of the line.
**
** return:	0 failed (the control->quit flag is raised)
**			1 ok
*/

int terminfo_refresh_screen_from_start(t_control *control)
{
	char *caps;

	if (!terminfo_cursor_move(control, 0, control->term->cursor_start.y))
		return (0);
	if (!(caps = terminfo_get_caps("ed", control)))
		return (0);
	tputs(caps, 1, ft_putchar);
	if (!terminfo_cursor_move_endl(control, 1))
		return (0);
	return (1);
}
