#include "minishell.h"

/*
** this file take scare of the cursor related functions using the terminfo
** utility.
*/


/*
** note:	this function will set the cursor's curent position in the
**			dedicated structure (inside control->term->cursor)
**
** RETURN:	1 ok
**			0 failure
*/

int		terminfo_cursor_get_pos(t_control *control)
{
	char *caps;

	if (!(caps = terminfo_get_caps("u7", control)))
		return (0);
	terminfo_cursor_get_pos_assist(caps, &(control->term->cursor));
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
** note:	this function will set the lenght of the prompt we last printed
**
** intput:	- the term struct
*/

void	terminfo_get_prompt_len(t_control *control)
{
	terminfo_cursor_get_pos(control);
	if (control->quit)
		return ;
	control->term->prompt_len = control->term->cursor.x - 1;
}

/*
** note:	this function will move the cursor to the right if possible
*/

void	terminfo_cursor_move_right(t_control *control)
{
	char *caps;

	if (!terminfo_cursor_get_pos(control))
		return ;
	if (control->term->inline_position + 1 < control->term->line_len)
	{
		if (control->term->cursor.x == control->term->size_window.x)
		{
			if (!(caps = terminfo_get_caps("ind", control)))
				return ;
			tputs(caps, 1, ft_putchar);
			control->term->inline_position++;
		}
		else
		{
			if (!(caps = terminfo_get_caps("cuf1", control)))
				return ;
			tputs(caps, 1, ft_putchar);
			control->term->inline_position++;
		}
	}
}

/*
** note:	this function will move the cursor to the left if possible
*/

void	terminfo_cursor_move_left(t_control *control)
{
	char *caps;

	if (!terminfo_cursor_get_pos(control))
		return ;
	if (control->term->inline_position >= 0)
	{
		if (control->term->cursor.x == 1)
		{
			if (!terminfo_cursor_move_diagonally(control, 1))
				return ;
		}
		else
		{
			if (!(caps = terminfo_get_caps("cub1", control)))
				return ;
			tputs(caps, 1, ft_putchar);
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
					control->term->cursor.y - 2))
			return (0);
		return (1);
	}
	else
	{
		if (control->term->cursor.y == control->term->size_window.y)
		{
			if (!(caps = terminfo_edit_caps(control, "indn", 1)))
				return (0);
			tputs(caps, 1, ft_putchar);
			if (!terminfo_cursor_move(control, 0, control->term->cursor.y + 1))
				return (0);
		}
		else if (!terminfo_cursor_move(control, 0, control->term->cursor.y))
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
	caps = tparm(caps, y, x);
	if (!(caps + 1))
	{
		control->quit = 1;
		return (0);
	}
	tputs(caps, 1, ft_putchar);
	return (1);
}
