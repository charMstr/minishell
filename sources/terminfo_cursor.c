#include "minishell.h"

/*
** this file take scare of the cursor related functions using the terminfo
** utility.
*/


/*
** note:	this function will set the cursor's curent position in the
**			dedicated structure (inside control->term->cursor)
*/

void	terminfo_cursor_get_pos(t_control *control)
{
	char *caps;
	caps = tigetstr("u7");
	if (!(caps + 1))
	{
		control->quit = 1;
		return ;
	}
	terminfo_cursor_get_pos_assist(caps, &(control->term->cursor));
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

	caps = tigetstr("cuf1");
	if (!(caps + 1))
	{
		control->quit = 1;
		return ;
	}
	// we sould later on treat the special case when we are at the end of the
	// line and there is still some text! need togo to the next line!
	if (control->term->inline_position < control->term->line_len)
	{
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

	caps = tigetstr("cub1");
	if (!(caps + 1))
	{
		control->quit = 1;
		return ;
	}
	// we sould later on treat the special case when we are at the end of the
	// line and there is still some text! need togo to the next line!
	if (control->term->inline_position > 0)
	{
		tputs(caps, 1, ft_putchar);
		control->term->inline_position--;
	}
}
