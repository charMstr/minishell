/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:47:34 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 11:47:34 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file is in charge of moving up and down in the history
*/

/*
** note:	this function swaps the current line with a line in history if
**			possible. The screen is redrawn from start, and if estimated number
**			of lines is bigger that the place we have from current start
**			position until bottom of screen the screen and the saved cursor
**			related are shifted accordingly.
*/

void	history_search(t_control *control, int direction)
{
	t_int_pair cursor_end;

	if (!history_swap_line_in_term_struct(control, direction))
		return ;
	if (!terminfo_refresh_screen_from_start(control))
		return ;
	cursor_end = terminfo_cursor_get_endl(control);
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

int		history_swap_line_in_term_struct(t_control *control, int up)
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
