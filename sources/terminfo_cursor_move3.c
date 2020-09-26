/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminfo_cursor_move3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 10:52:46 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 23:58:55 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file contains the functions relative to moving the cursor left or right
** one word (ctrl + left or right arrow)
*/

/*
** note:	this function will move the cursor to the begining of the next word
**			if possible. (if we are in the middle of the last or only word we
**			will do nothing.)
**
** return:	1 ok
**			0 failure (the control->quit flag is raised byt the subfunctions)
*/

int		terminfo_cursor_move_next_word(t_control *control)
{
	int index;
	int	right_motion;
	int j;
	int	current_len;

	j = 0;
	if (-1 == (index = terminfo_cursor_find_next_word_start(control)))
		return (1);
	right_motion = index - control->term->inline_position - 1;
	while (j < right_motion)
	{
		current_len = terminfo_predict_current_line_len(control);
		terminfo_cursor_track_position(control, 1);
		if (control->term->cursor.x == current_len)
			terminfo_cursor_move_diagonally_down(control);
		control->term->inline_position++;
		j++;
	}
	if (!terminfo_cursor_move(control, control->term->cursor.x, \
				control->term->cursor.y))
		return (0);
	return (1);
}

/*
** note:	this function will find the index of the beginnig of the next word
**			in the current line we are editing. Whitespaces are considered to
**			be <space> and <newline>.
**
** RETURN:	-1 not found
**			else: the index
*/

int		terminfo_cursor_find_next_word_start(t_control *control)
{
	int		i;
	char	*str;

	if ((str = control->term->line) == NULL)
		return (-1);
	i = control->term->inline_position + 1;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\n')
		{
			while (str[i] && (str[i] == ' ' || str[i] == '\n'))
				i++;
			if (str[i])
				return (i);
			else
				return (-1);
		}
		i++;
	}
	return (-1);
}

/*
** note:	this function will move the cursor to the begining of the previsous
**			word if possible. (if we are in the middle of the first or only
**			word we will do nothing.)
**
** return:	1 ok
**			0 failure (the control->quit flag is raised byt the subfunctions)
*/

int		terminfo_cursor_move_previous_word(t_control *control)
{
	int index;
	int	left_motion;
	int j;

	j = 0;
	if (-1 == (index = terminfo_cursor_find_previous_word_start(control)))
		return (1);
	left_motion = control->term->inline_position + 1 - index;
	while (j < left_motion)
	{
		terminfo_cursor_track_position(control, 0);
		control->term->inline_position--;
		j++;
	}
	if (!terminfo_cursor_move(control, control->term->cursor.x, \
				control->term->cursor.y))
		return (0);
	return (1);
}

/*
** note:	this function will RETURN the address of the begining of the
**			current word or the previsous if we are in a whitespace area.
**
** RETURN:	-	index if ok.
**			-	-1 not possible (exemple, we are in whitespace and there is no
**				characters to the left).
*/

int		terminfo_cursor_find_previous_word_start(t_control *control)
{
	int		i;
	char	*str;

	str = control->term->line;
	i = control->term->inline_position;
	if (i == -1)
		return (-1);
	while (str[i] && (str[i] == ' ' || str[i] == '\n'))
		i--;
	if (i == -1)
		return (-1);
	while (i >= 0)
	{
		if (str[i] == ' ' || str[i] == '\n')
			return (i + 1);
		i--;
	}
	return (0);
}
