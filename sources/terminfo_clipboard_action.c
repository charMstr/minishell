#include "minishell.h"

/*
** note:	this function takes care of the right motion while in the highlight
**			mode.
** RETURN:	1 ok
**			0 failure
*/

int	terminfo_clipboard_right_move(t_control *control, t_clipboard *clipboard)
{
	if (control->term->inline_position + 2 == control->term->line_len)
		return (1);
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
	if (control->term->inline_position >= 0)
		clipboard->end--;
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
	len_rest = control->term->line_len - clipboard->end - 1;
	len_cut = clipboard->end - clipboard->start + 1;
	i = 1;
	if (!clipboard->swaped_end)
	{
		while (i < len_cut)
		{
			terminfo_cursor_track_position(control, 0);
			i++;
			control->term->inline_position--;
		}
	}
	ft_memmove(str + clipboard->start, str + clipboard->end + 1, len_rest + 1);
	control->term->line_len -= len_cut;
	if (!terminfo_refresh_screen_from_start(control))
		return (0);
	return (1);
}

/*
** note:	this function will be in charge of pasting the text contained in
**			the clipboard in place.
**
** RETURN:	1 ok
**			0 ko
*/

int	terminfo_clipboard_paste(t_control *control, t_clipboard *clipboard)
{
	int len_paste_me;
	int	i;
	t_int_pair cursor_end;

	if (!clipboard->paste_me)
		return (1);
	len_paste_me = ft_strlen(clipboard->paste_me);
	i = -1;
	if (!(ft_strstradd(&control->term->line, \
					control->term->inline_position + 1, clipboard->paste_me)))
		return (0);
	control->term->line_len += len_paste_me;
	cursor_end = terminfo_cursor_get_endl(control);
	while (clipboard->paste_me[++i] \
			&& cursor_end.y >= control->term->size_window.y)
	{
		if (clipboard->paste_me[i] == '\n' && (control->term->cursor.y--))
			cursor_end.y--;
	}
	control->term->clipboard.highlight = 0;
	if (!terminfo_refresh_screen_from_start(control))
		return (0);
	return (1);
}
