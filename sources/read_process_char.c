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
		/*
		   GO UP AND DOWN IN HISTORIC HAPPENS HERE
		//printf("ID of special sequence is: [%d]\n", i);
		if (i == 1)//move up				OK need to go up in history
		{
			char *caps = tigetstr("cuu1");
			tputs(caps, 1, ft_putchar);
		}
		if (i == 4)//move down				OK need to go down in history
		{
			char *caps = tigetstr("cud");
			tputs(tparm(caps, 1), 1, ft_putchar);
		}
		*/
}
