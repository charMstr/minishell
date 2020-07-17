#include "minishell.h"

/*
** note:	this function will load in the array_esc_seq an array of strings
**			matching the potential escaped sequence we can receive from
**			the keyboard (the strings are yielded from the terminfo database).
**				- UP, DOWN, RIGHT and LEFT arrows.
**				- End, Home, Page up, Page down and Delete keys.
** input:	- term: structure with member array_esc_seq to be filled
**
** RETURN:	1 OK
**			0 if failure
*/

int	terminfo_load_array_esc_seq(t_term *term)
{
	char	**array;
	int		i;

	array = (char *[]){KEY_ESC_, KEY_UP_, KEY_RIGHT_,
		KEY_LEFT_, KEY_DOWN_, KEY_HOME_, KEY_DELETE_, KEY_END_, KEY_PAGE_UP_,
		KEY_PAGE_DOWN_, KEY_UP_CTRL_, KEY_DOWN_CTRL_, KEY_RIGHT_CTRL_,
		KEY_LEFT_CTRL_ , NULL};
	i = 0;
	if (!(term->array_esc_seq = (char **)malloc(sizeof(char *) * (1 + \
						NUMBER_SPECIAL_KEYS))))
		return (0);
	term->array_esc_seq[NUMBER_SPECIAL_KEYS] = NULL;
	while (i < NUMBER_SPECIAL_KEYS)
	{
		if (!(term->array_esc_seq[i] = ft_strdup((char *)array[i])))
		{
			ft_array_free(term->array_esc_seq, i);
			return (0);
		}
		i++;
	}
	return (1);
}

/*
** note:	this function is first calling the  terminfo_get_caps() func
**			then it will inject in the string the parameters using tparm()
** note:	if a failure occure: the control->quit flag is raised
**
** intput:	-	caps_id: to be sent to tigetstr (in terminfo_get_caps)
**			-	param: to be injected in the string
**			-	control sruct
**
** RETURN:	char *
**			NULL;
*/

char *terminfo_edit_caps(t_control *control, char *caps_id, int param)
{
	char *caps;

	if (!(caps = terminfo_get_caps(caps_id, control)))
		return (NULL);
	caps = tparm(caps, param);
	if (!(caps + 1))
	{
		control->quit = 1;
		return (NULL);
	}
	return (caps);
}

/*
** note:	This function will return the string the desired escape sequence
**			when consulting database through tigetstr().
**			The control->quit flag is raised if the fucntion fails.
**
** note:	the returned pointer is 0xffffffffff in the case tigetstr() failed
**			therefor we need to add one and compare to NULL
**
** usage:	if (!(caps == terminfo_get_caps("...", control)))
**				return ;
**
** RETURN:	char *
**			NULL
*/

char *terminfo_get_caps(char *caps_id, t_control *control)
{
	char *caps;

	caps = tigetstr(caps_id);
	if (!(caps + 1))
	{
		control->quit = 1;
		return (NULL);
	}
	return (caps);
}

/*
** note:	this function will refresh the screen from start of the line until
**			the bottom of the screen.
**
** note:	according to documentation, to use "ed" we need to be place on the
**			index ZERO of the line.
** note:	the cursor's position is saved and restaured. the prompt and the
**			line are redrawned.
**
** return:	0 failed (the control->quit flag is raised)
**			1 ok
*/

int terminfo_refresh_screen_from_start(t_control *control)
{
	char *caps;

	control->term->cursor_saved = control->term->cursor;
	if (!terminfo_update_bottom_screen_and_cursor(control))
		return (0);
	if (!terminfo_cursor_move(control, 0, control->term->cursor_start.y))
		return (0);
	if (!(caps = terminfo_get_caps("ed", control)))
		return (0);
	tputs(caps, 1, ft_putchar);
	if (control->term->prompt_ps1)
		ft_putstr_fd(control->term->ps1, 2);
	else
		ft_putstr_fd(control->term->ps2, 2);
	ft_putstr_fd(control->term->line, 1);
	if (!(terminfo_cursor_saved_reset(control)))
		return (0);
	return (1);
}

/*
** note:	this function is called when refreshing the screen. we compare the
**			cursor_end.y with the window height. Depending on the result, we
**			shift the screen up, and we update accordingly the related var.
**
** RETURN:	1 ok
**			0 failure
*/

int	terminfo_update_bottom_screen_and_cursor(t_control *control)
{
	t_int_pair cursor_end;
	char *caps;

	cursor_end = terminfo_cursor_get_endl(control);
	if (!(caps = terminfo_get_caps("ind", control)))
		return (0);
	while (cursor_end.y >= control->term->size_window.y)
	{
		cursor_end.y--;
		control->term->cursor_start.y--;
		tputs(caps, 1, ft_putchar);
	}
	return (1);
}
