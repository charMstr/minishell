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
	if (!terminfo_cursor_track_position(control, 0))
		return (0);
	if (!terminfo_refresh_screen_from_start(control))
		return (0);
	return (1);
}
