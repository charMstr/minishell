#include "minishell.h"

/*
** this file is in charge of moving up and down in the history
*/

/*
** note:
*/

void	history_search(t_control *control, int direction)
{
	t_int_pair cursor_end;

	if (!history_swap_line_in_term_struct(control, direction))
		return ;
	cursor_end = terminfo_cursor_get_endl(control);
	if (!terminfo_refresh_screen_from_start(control))
		return ;
	if (!history_terminfo_reset_cursor(control, &cursor_end))
		return ;
	if (control->first_time)
		ft_putstr_fd(control->term->ps1, 2);
	else
		ft_putstr_fd(control->term->ps2, 2);
	ft_putstr_fd(control->term->line, 1);
	control->term->cursor = cursor_end;
	terminfo_cursor_move(control, cursor_end.x, cursor_end.y);
}

/*
** note:	this function will simply get the next or previous link in the
**			history linked list, if the link exists:
**			-	The strings it contains is copied in the current line we are
**				editing(control->term->line)
**			-	The control->term->current_link points to that new_link
**
** note:	if ft_strdup failed: quit flag is raised.
**
** RETURN:	1 process to change
**			0 do not
*/

int	history_swap_line_in_term_struct(t_control *control, int up)
{
	t_dlist	*new_link;
	char	*old_str;

	if (up == 1)
		new_link = control->term->current_history_link->next;
	else
		new_link = control->term->current_history_link->previous;
	if (!new_link)
		return (0);
	old_str = control->term->line;
	if (!(control->term->line = ft_strdup((char *)(new_link->content))))
	{
		control->quit = 1;
		return (0);
	}
	ft_free((void **)&old_str);
	control->term->current_history_link = new_link;
	control->term->line_len = ft_strlen((char*)(new_link->content));
	control->term->inline_position = control->term->line_len - 1;
	return (1);
}

/*
** note:	this function will totally reset the cursor at the new correct
**			place according to the new line's length.
**			if cursor_end is too low, everything gets shifted upwards.
**
** RETURN:	1 OK
**			0 failure.
*/

int	history_terminfo_reset_cursor(t_control *control, t_int_pair *cursor_end)
{
	char *caps;

	if (!(caps = terminfo_get_caps("ind", control)))
		return (0);
	while (cursor_end->y >= control->term->size_window.y)
	{
		cursor_end->y--;
		control->term->cursor_start.y--;
		tputs(caps, 1, ft_putchar);
	}
	if (!terminfo_cursor_move(control, 0, control->term->cursor_start.y))
		return (0);
	return (1);
}
