#include "minishell.h"

/*
** note:	this function takes care of the right motion while in the highlight
**			mode.
** RETURN:	1 ok
**			0 failure
*/

int	terminfo_clipboard_right_move(t_control *control, t_clipboard *clipboard)
{
	if (control->term->inline_position + 1 < clipboard->start)
	{
		if (!terminfo_clipboard_highlight_cur(control, 0))
			return (0);
		if (!terminfo_cursor_move_right(control))
			return (0);
	}
	else
	{
		if (!terminfo_cursor_move_right(control))
			return (0);
		if (!terminfo_clipboard_highlight_cur(control, 1))
			return (0);
	}
	clipboard->end++;
	return (1);
}

/*
** note:	this function takes care of the lett motion while in the highlight
**			mode.
**
** RETURN:	1 ok
**			0 failure
*/

int	terminfo_clipboard_left_move(t_control *control, t_clipboard *clipboard)
{
	if (control->term->inline_position + 1 > clipboard->start)
	{
		if (!terminfo_clipboard_highlight_cur(control, 0))
			return (0);
		if (!terminfo_cursor_move_left(control))
			return (0);
	}
	else
	{
		if (!terminfo_cursor_move_left(control))
			return (0);
		if (!terminfo_clipboard_highlight_cur(control, 1))
			return (0);
	}
	clipboard->end--;
	return (1);
}

/*
** note:	this function is in charge of cuting the highlighted text section
**
** RETURN:	1 ok
**			0 failure
*/

int	terminfo_clipboard_cut(t_control *control, t_clipboard *clipboard)
{
	char	*str;
	int		len_rest;
	int		len_cut;
	int		i;

	str = control->term->line;
	len_rest = control->term->line_len - clipboard->end;
	ft_memmove(str + clipboard->start, str + clipboard->end + 1, len_rest);
	len_cut = clipboard->end - clipboard->start;
	i = 0;
	if (!clipboard->swaped_end)
	{
		while (i < len_cut)
		{
			terminfo_cursor_track_position(control, 0);
			i++;
		}
		control->term->inline_position -= len_cut;
	}
	control->term->line_len -= len_cut + 1;
	if (!terminfo_refresh_screen_from_start(control))
		return (0);
	return (1);
}
