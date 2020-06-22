#include "minishell.h"

/*
** this is the root file taking care of reading from stdin until either:
**	-	ctrl_c is pressed
**	-	ctrl_d is pressed and current line is empty
**	-	ENTER is pressed
**	- 	failure in malloc
**	-	failure in read or write?
*/

/*
** note:	root function for reading from the terminal.
**			The	main purpose is to update the control->term->line field
**			Depending on the flags being raised or not. we will either reprompt
**			or process with that line:
**				1) deciding how to append it in the current line history
**				2) if ok, we sent the whole current line hist to lexer.
*/

void	read_root(t_control *control, int read_res, char c)
{
	while (1)
	{
		read_res = read(STDIN_FILENO, &c, 1);
		if (!read_res)
			continue;
		if (c == '\n')
			break;
		if (read_need_to_stop(control, c, read_res))
			return ;
		read_dispatch_for_processing(control, c);
		if (read_need_to_stop(control, c, read_res))
			return ;
	}
}

/*
** note:	this function is started if we read the character 27. we need to
**			differenciate the case when it is actually the 'esc' key or a
**			termcap sequence representing a special key. The c value is
**			remaped starting from 128. Then we can recognize a left/right arrow
**			at this stage and use it for the copy/paste functions.
**
** return: a remap value starting from 128.
*/

int	read_remap_esc_sequence_from_128(t_control *control, int c)
{
	c = read_get_esc_seq_id(control->term, c) + 128;
	if (c == -1)
	{
		control->quit = 1;
		return (0);
	}
	return (c);
}

/*
** note:	this function will analyse the char we read and act accordingly
**			ethier moving the cursor etc, or appending/inserting the new char
**			to the current line (in control->term->line)
**
** input:	-	control struct
**			-	c: the current character we just read
**			-	count: the updated number of written characters since prompt.
*/

void	read_dispatch_for_processing(t_control *control, int c)
{
	if (c == 27 && !(c = read_remap_esc_sequence_from_128(control, c)))
			return ;
	if (control->term->clipboard.highlight)
	{
		if (c != KEY_LEFT_ID && c != KEY_RIGHT_ID && c != CTRL_K_COMBO \
				&& c != CTRL_L_COMBO)
			terminfo_clipboard_copy_end(control, &control->term->clipboard);
		else
		{
			terminfo_clipboard_dispatch_action(control, c);
			return ;
		}
	}
	if (c == CTRL_K_COMBO)
		terminfo_clipboard_copy_start(control, &control->term->clipboard);
	else if (c >= 128)
		read_process_special_key(control, c);
	else if (c == 127)
		read_process_del_char(control);
	else if (!ft_isprint(c))
		read_process_control_combo(control, c);
	else
		read_process_add_char(control, c);
}

/*
** note:	this function will analyse the last read character and decide
**			if we need to stop reading or not
**
** input:	- count: the number of characters in the current line so far
**			- res: the return from the last read
**			- c: the last char read
**			- control struct.
**
** RETURN:	0 keep reading
**			1 stop reading
*/

int	read_need_to_stop(t_control *control, char c, int res)
{
	if (control->quit)
		;
	else if (res == -1)
	{
		control->quit = 1;
		//maybe display message for a read failure
		//maybe set control->exit_status...
	}
	else if (c == 4 && !control->term->line_len)
	{
		control->quit = 1;
		ft_putstr_fd("exit", 2);
	}
	else if (c == 3)
	{
		control->exit_status = 1;
		control->ctrl_c = 1;
	}
	else
		return (0);
	return (1);
}

/*
** note:	this function will return the ID of the escaped sequence yielded
**			from the key stroke at the keyboard. (up, right, left, down, end,
**			home, delete, page_up, page_down)
**
** RETURN:	ID
**			0 if only the 'esc' key was typed. (because of the timeout on read)
**			-1 if failure
*/

int	read_get_esc_seq_id(t_term *term, int c)
{
	int res_read;
	char *str;
	int i;

	str = NULL;
	if (!ft_strappend(&str, c))
		return (-1);
	while ((res_read = read(STDIN_FILENO, &c, 1)) && (i = -1))
	{
		if (res_read == -1 || !ft_strappend(&str, c))
		{
			free(str);
			return (-1);
		}
		while (++i < NUMBER_SPECIAL_KEYS)
		{
			if (!ft_strncmp(str, term->array_esc_seq[i], ft_strlen(str) + 1))
			{
				free(str);
				return (i);
			}
		}
	}
	free(str);
	return (0);
}
