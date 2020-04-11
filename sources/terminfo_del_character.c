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
	char *caps;

	if (!terminfo_cursor_get_pos(control, &(control->term->cursor)))
		return (0);
	if (control->term->cursor.x)
	{
		if (!(caps = terminfo_get_caps("cub1", control)))
			return (0);
		tputs(caps, 1, ft_putchar);
		if (!(caps = terminfo_edit_caps(control, "dch1", 1)))
			return (0);
		tputs(caps, 1, ft_putchar);
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

