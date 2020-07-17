#include "minishell.h"

/*
** this file contains the root function for copy/cut/past bonus.
** the text will be highlighted while selecting it. the ctrl_V will print
** whatever is in the clipboard for the lifespan of the minishell program.
*/

/*
** note:	this is the function called when we first do the ctrl+k combo, the
**			control->term->clipboard->highlight is set to one.
** note:	we cannot highlight when the cursor is sitting after the line.
** note:	The cursor is always one place ahead of the index we are at. so we
**			need to highlight the character at inline_position + 1(the one the
**			cursor is "sitting on").
**
** RETURN:	1 ok.
**			0 malloc failed, control->quit is raised.
*/

int terminfo_clipboard_copy_start(t_control *control, t_clipboard *clipboard)
{
	char *caps;

	if (!control->term->line)
		return (1);
	if (control->term->inline_position + 1 == control->term->line_len)
		return (1);
	ft_free((void**)&clipboard->paste_me);
	if (!(caps = terminfo_get_caps("smso", control)))
		return (0);
	tputs(caps, 1, ft_putchar);
	clipboard->start = control->term->inline_position + 1;
	clipboard->end = control->term->inline_position + 1;
	clipboard->highlight = 1;
	clipboard->swaped_end = 0;
	if (!terminfo_clipboard_highlight_cur(control, 1))
		return (0);
	return (1);
}

/*
** note:	This function is called when we were in highlight mode, but the
**			character typed in at the prompt was neither '<', '>', ctrl_K or
**			ctrl_L. the screen is redrawn from the prompt so that we dont see
**			the highlighting no more.
** note:	the cursor is replaced in its original position and
** RETURN:	1 ok
**			0 failure
*/

int	terminfo_clipboard_copy_end(t_control *control, t_clipboard *clipboard)
{
	if (!terminfo_clipboard_disable_highlight(control))
		return (0);
	if (!terminfo_refresh_screen_from_start(control))
		return (0);
	if (clipboard->start > clipboard->end)
	{
		clipboard->start ^= clipboard->end;
		clipboard->end ^= clipboard->start;
		clipboard->start ^= clipboard->end;
		clipboard->swaped_end = 1;
	}
	if (!(clipboard->paste_me = ft_substr(control->term->line, \
				clipboard->start, clipboard->end - clipboard->start + 1)))
	{
		control->quit = 1;
		return (0);
	}
	return (1);
}

/*
** note:	this function is just practical, one liner.
**
** RETURN:	1 ok
**			0 failure
*/

int	terminfo_clipboard_disable_highlight(t_control *control)
{
	char *caps;

	control->term->clipboard.highlight = 0;
	if (!(caps = terminfo_get_caps("rmso", control)))
		return (0);
	tputs(caps, 1, ft_putchar);
	return (1);
}

/*
** note:	this function will reprint the characater in place where the cursor
**			is. In "standout" mode or not depending on an option. We always
**			reset in place the cursor.
**
** RETURN:	1 ok
**			0 failure.
*/

int	terminfo_clipboard_highlight_cur(t_control *control, int on)
{
	char c;
	char *caps;

	if (!on)
	{
		if (!(caps = terminfo_get_caps("rmso", control)))
			return (0);
		tputs(caps, 1, ft_putchar);
	}
	c = control->term->line[control->term->inline_position + 1];
	ft_putchar_fd(c, 1);
	if (!terminfo_cursor_move(control, control->term->cursor.x, \
				control->term->cursor.y))
		return (0);
	if (!on)
	{
		if (!(caps = terminfo_get_caps("smso", control)))
			return (0);
		tputs(caps, 1, ft_putchar);
	}
	return (1);
}

/*
** note:	This function is called when we are currently in highliht mode, and
**			the character typed in is either: left arrow, right arrow, ctrl_k
**			(for end of copy), or ctrl_L (for cut).
**
** RETURN:	1 ok
**			0 failure
*/

int	terminfo_clipboard_dispatch_action(t_control *control, int c)
{
	if (c == KEY_RIGHT_ID)
	{
		if (!terminfo_clipboard_right_move(control, &control->term->clipboard))
			return (0);
	}
	else if (c == KEY_LEFT_ID)
	{
		if (!terminfo_clipboard_left_move(control, &control->term->clipboard))
			return (0);
	}
	else if (c == CTRL_K_COMBO)
	{
		if (!terminfo_clipboard_copy_end(control, &control->term->clipboard))
			return (0);
		control->term->clipboard.highlight = 0;
	}
	else if (c == CTRL_L_COMBO)
	{
		if (!terminfo_clipboard_copy_end(control, &control->term->clipboard))
			return (0);
		if (!terminfo_clipboard_cut(control, &control->term->clipboard))
			return (0);
		control->term->clipboard.highlight = 0;
	}
	return (1);
}
