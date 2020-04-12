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
		// we need to recheck the flags, especiall control->quit if something
		//went wrong (malloc, failure terminfo failure...)
		if (read_need_to_stop(control, c, read_res))
			return ;
	}
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

void	read_dispatch_for_processing(t_control *control, char c)
{
	//debug_value_char(c);
	if (c == 27)
		read_process_special_key(control, c);
	else if (c == 127)
		read_process_del_char(control);
	else if (!ft_isprint(c))
		read_process_control_combo(control, c);
	/*
	else if (c == 'g')
	{
		terminfo_cursor_get_pos(control, &(control->term->cursor));
		debug_cursor(&(control->term->cursor));
		debug_term_size();
	}
	*/
	else
		read_process_add_char(control, c);
}

/*
		//debug_value_char(c);
		if (c == 127)//trying to del
		{
				//char *caps = tigetstr("cud");
				//tputs(tparm(caps, 1), 1, ft_putchar);
 //erase the whole line. cursor does not move:
 //if there is a line under, it just gets shifted up as is:
				//ft_putstr_fd("\033[M", 1);
 //erase in place (exactly like the 'delete==>' key would do)
 //whatever was on the right gets shifted to the left 1 column. (BUT NOT WHAT ON THE NEXT LINE)
 // ===> combined with a left move of the cursor first,  [THIS IS THE ONE]			++++++
				//char *caps = tigetstr("cub1");
				//tputs(caps, 1, ft_putchar);
				//ft_putstr_fd("\033[P", 1); or its equivalent:
				// 	char *caps = tigetstr("dch");
				//	tputs(tparm(caps, 1), 1, ft_putchar);
 //erase everything from the cursor to the bottom of the screen (the end of the line as well ;) )
				//ft_putstr_fd("\033[J", 1);
 //erase everything from the cursor postion until the end of the line (but not the next one)
				//ft_putstr_fd("\033[K", 1);
 //erase everything from the cursor postion(included) until the BEGINING of the line:
				//ft_putstr_fd("\033[1K", 1);

 //insert a blank line in position and shift the curent line and under downards
				//ft_putstr_fd("\033[L", 1);
//set the cursor HOME: top left corner
				//ft_putstr_fd("\033[H", 1);
//makes space in order to insert a char, but we still need to figure out how to		++++++++
//actually insert a char after the space is made.
				//char *caps = tigetstr("ich");
				//tputs(tparm(caps, 1), 1, ft_putchar);
//places the cursor on the next line, at the beginning of the line					++++++++
				//char *caps = tigetstr("ind");
				//tputs(caps, 1, ft_putchar);
//the cursor does not move, but the whole screen shifts up.
				//char *caps = tigetstr("indn");
				//tputs(tparm(caps, 1), 1, ft_putchar);
//move the cursor to the indicated column and row
				//char *caps = tigetstr("cup");
				//tputs(tparm(caps, 10, 10), 1, ft_putchar);
//save cursor position
				//char *caps = tigetstr("sc");
				//tputs(caps, 1, ft_putchar);
//restor cursor to that position
				//char *caps = tigetstr("rc");
				//tputs(caps, 1, ft_putchar);

				//debug_escape_sequence(caps);
		}
}
*/

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
	if (control->quit) //this could happen if the terminfo function failed...
		return (1);
	if (res == -1)
	{
		//maybe display message for a read failure
		//maybe set control->exit_status...
		return (1);
	}
	if (c == 4 && !control->term->line_len)
	{
		control->quit = 1;
		return (1);
	}
	if (c == 3)
	{
		control->ctrl_c = 1;
		return (1);
	}
	return (0);
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

int	read_get_esc_seq_id(t_term *term, char c)
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
//	debug_escape_sequence(str);
	free(str);
	return (0);
}
