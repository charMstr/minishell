/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminfo_insert_character.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 10:37:18 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 10:38:31 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file is in charge of inserting to the screen the charcter, and
** especially the lines if we are in a multiline situation.
*/

/*
** note:	this function is the base for inserting a character in the screen
**
** RETURN:	1 ok
**			0 failure
*/

int		terminfo_insert_char(t_control *control, char c)
{
	int cur_line_len;
	int	saved_inline_position;

	cur_line_len = terminfo_predict_current_line_len(control);
	if (cur_line_len == control->term->size_window.x)
	{
		control->term->cursor_saved = control->term->cursor;
		saved_inline_position = control->term->inline_position;
		if (!terminfo_insert_char_cascade(control))
			return (0);
		if (!(terminfo_cursor_saved_reset(control)))
			return (0);
		control->term->inline_position = saved_inline_position;
	}
	if (!terminfo_insert_in_place(control, c))
		return (0);
	if (!(terminfo_cursor_track_position(control, 1)))
		return (0);
	return (1);
}

/*
** note:	this function is in charge of inserting in the screen the given
**			char, in place.
**
** RETURN:	1 ok
**			0 failure
*/

int		terminfo_insert_in_place(t_control *control, char c)
{
	char *caps;

	if (c != '\n')
	{
		if (!(caps = terminfo_edit_caps(control, "ich", 1)))
			return (0);
		tputs(caps, 1, ft_putchar);
		ft_putchar_fd(c, 1);
	}
	else if (!terminfo_insert_newline(control))
		return (0);
	return (1);
}

/*
** note:	this function is customed for the case we need to cascade a '\n'
**			while editing a command unfiched quote-wise with newlines.
**			If while inserting, we are at the bottom of the screen, we need to
**			shift evertything up.
** return:	1 ok
**			0 failure
*/

int		terminfo_insert_newline(t_control *control)
{
	char		*caps;
	t_int_pair	cursor_end;

	cursor_end = terminfo_cursor_get_endl(control);
	if (cursor_end.y >= control->term->size_window.y)
	{
		if (!(caps = terminfo_edit_caps(control, "indn", 1)))
			return (0);
		tputs(caps, 1, ft_putchar);
		control->term->cursor.y--;
		control->term->cursor_saved.y--;
		control->term->cursor_start.y--;
		if (!terminfo_cursor_move(control, control->term->cursor.x,\
					control->term->cursor.y))
			return (0);
	}
	if (!(caps = terminfo_get_caps("il1", control)))
		return (0);
	tputs(caps, 1, ft_putchar);
	return (1);
}

/*
** note:	This function will check if the insertion of the character in the
**			display shifts the last character of the line outside of the
**			screen. If so, the characters are inserted at the beginning of the
**			next line in cascade.
**
** note:	the character at this stage has been inserted, and term->len_line,
**			and term->inline_position have been updated (++).
**			BUT NOT control->term->cursor neither the cursor position.
**
** return:	1 ok
**			0 failure
*/

int		terminfo_insert_char_cascade(t_control *control)
{
	char	cascade_me;
	char	*str;
	int		offset;
	int		end_index;

	str = control->term->line;
	while (terminfo_predict_current_line_len(control) \
			== control->term->size_window.x)
	{
		end_index = terminfo_predict_current_line_end_index(control);
		offset = end_index - control->term->inline_position;
		cascade_me = str[end_index];
		if (!terminfo_cursor_move_diagonally_down(control))
			return (0);
		if (!terminfo_insert_in_place(control, cascade_me))
			return (0);
		control->term->inline_position += offset;
		if (control->term->inline_position >= control->term->line_len)
			break ;
	}
	return (1);
}
