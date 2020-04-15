#include "minishell.h"

/*
** this file takes care of predicing the length of the lines regarding the fact
** that they dont have to be as wide of the screen when going up in history and
** encountering a command partially quoted and containing '\n'.
**
** note:	the length of the line is always obtained considering the current
**			position of the cursor, and the current index we are at in line,
**			until a '\n' is reached or the control->term->size_window.x is met.
*/

/*
** note:	this function preditcs the length of the current line on the
**			display.
*/

int terminfo_predict_current_line_len(t_control *control)
{
	int	i;
	int	j;
	char *str;

	i = control->term->cursor.x;
	j = control->term->inline_position + 1;
	str = control->term->line;
	if (!str)
		return (control->term->prompt_len);
	while (i < control->term->size_window.x && str[j] && str[j] != '\n')
	{
		i++;
		j++;
	}
	if (str[j] == '\n' && i != control->term->size_window.x)
		return (++i);
	return (i);
}

/*
** note:	this function will return the index of the character that seats at
**			the end of the current line visually speaking
** note:	this gives the position where the '\0' or the '\n' would be if the
**			line is shorter than the control->term->size_window.
**
** note:	if you print that char you get the char that is on the right most
**			column of the screen.
*/

int terminfo_predict_current_line_end_index(t_control *control)
{
	int	i;
	int	j;
	char *str;

	i = control->term->cursor.x;
	j = control->term->inline_position + 1;
	str = control->term->line;
	if (!str)
		return (0);
	while (i + 1 < control->term->size_window.x && str[j] && str[j] != '\n')
	{
		i++;
		j++;
	}
	return (j);
}

/*
** note:	this function will return the index of the character that seats at
**			the start of the current line visually speaking
** note:	if you print that char, you get the char that was on the first
**			left column of the screen.
*/

int terminfo_predict_current_line_start_index(t_control *control)
{
	int	i;
	int	j;
	char *str;

	i = control->term->cursor.x;
	j = control->term->inline_position + 1;
	str = control->term->line;
	if (!str)
		return (0);
	if (str[j] == '\n' && i != 0)
	{
		i--;
		j--;
	}
	while (i > 0 && j > 0 && str[j] != '\n')
	{
		i--;
		j--;
	}
	return (j);
}

/*
** note:	this function will predict the cursor's cordinates at the end of
**			the previous line.
** note:	do not call this function if we are on the first line.
*/

t_int_pair	terminfo_predict_previous_line_cursor_end(t_control *control)
{
	t_int_pair end_previous;
	int		end_index_prev;
	int		i;
	char	*str;

	i = 0;
	end_previous = control->term->cursor_start;
	end_index_prev = terminfo_predict_current_line_start_index(control) - 1;
	str = control->term->line;
	while (i < end_index_prev)
	{
		if (str[i] == '\n' \
				|| end_previous.x  + 1 == control->term->size_window.x)
		{
			end_previous.x = 0;
			end_previous.y++;
		}
		else
			end_previous.x++;
		i++;
	}
	return (end_previous);
}

/*
** note:	this function preditcs the length of the next line on the display.
*/

//not used unused for now...
int terminfo_predict_next_line_len(t_control *control) //OK 100%
{
	int i;
	int	j;
	char *str;

	i = 0;
	j = terminfo_predict_current_line_end_index(control);
	str = control->term->line;
	if (!str || !str[j])
		return (0);
	j++;
	while (i + 1 < control->term->size_window.x && str[j] && str[j] != '\n')
	{
		j++;
		i++;
	}
	if (str[j] == '\n')
		i++;
	return (i);
}
