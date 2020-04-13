#include "minishell.h"

/*
** this file is assisting the file read_root
*/

/*
** note:	this function is in charge of adding a character that if printable
*/

void	read_process_add_char(t_control *control, char c)
{
	if (!(ft_strcadd(&(control->term->line), c, \
					control->term->inline_position + 1)))
	{
		control->quit = 1;
		return ;
	}
	control->term->inline_position++;
	control->term->line_len++;
	if (!terminfo_insert_char(control, c))
	{
		control->quit = 1;
		return ;
	}
}

/*
 ** note:	this function will delete effectively a character from the curent
 **			string, if the cursor is not against the prompt.
 */

void	read_process_del_char(t_control *control)
{
	if (control->term->inline_position == -1)
		return ;
	if (!terminfo_del_char(control))
		return ;
	if (!ft_strcdel(&(control->term->line), control->term->inline_position))
	{
		control->quit = 1;
		return ;
	}
	control->term->inline_position--;
	control->term->line_len--;
}

/*
** note:	this function will be called when a special key is hit on the
**			keyboard: either one of the arrows, 'delete=>', 'home', 'end',
**			'page_down', 'page_up', or 'esc'.
** input:	-	control struct
**			-	c: the '\033' sequence.
*/

void	read_process_special_key(t_control *control, char c)
{
		int i;

		if (-1 == (i = read_get_esc_seq_id(control->term, c)))
		{
			control->quit = 1;
			return;
		}
		if (i == KEY_RIGHT_ID)
			terminfo_cursor_move_right(control);
		else if (i == KEY_LEFT_ID)
			terminfo_cursor_move_left(control);
		else if (i == KEY_HOME_ID)
			read_process_control_combo(control, CTRL_A_COMBO);
		else if (i == KEY_END_ID)
			read_process_control_combo(control, CTRL_E_COMBO);
		else if (i == KEY_UP_CTRL_ID)
			terminfo_cursor_move_up(control);
		else if (i == KEY_DOWN_CTRL_ID)
			terminfo_cursor_move_down(control);
		else if (i == KEY_RIGHT_CTRL_ID)
			terminfo_cursor_move_next_word(control);
		else if (i == KEY_LEFT_CTRL_ID)
			terminfo_cursor_move_previous_word(control);
		else
			read_process_special_key2(control, i);
}

/*
** note:	see number one for man.
*/

void	read_process_special_key2(t_control *control, int i)
{
	if (i == KEY_UP_ID)
		history_search(control, 1);
	else if (i == KEY_DOWN_ID)
		history_search(control, 0);
}
