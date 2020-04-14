#include "minishell.h"

/*
** this file is in charge of updateing the historic, deciding how to add the
** line we got from the prompt to the current link. and deciding if we keep or
** discard that link.
*/

/*
** note:	this function is due for appending the last input to the current
**			line of the history link. if there is a PS2: this is where the
**			concatenation happens.
**
** RETURN:	1 ok
**			0 something failed. (flag control->quit raised accordingly)
*/

int	history_update_line(t_control *control, t_history *history)
{
	char *current_hist;
	char *str;

	current_hist = (char *)(history->head->content);
	if (control->lexer_end.backslash)
		current_hist[ft_strlen(current_hist) - 1] = '\0';
	if (control->lexer_end.quote)
	{
		if (!history_update_line_quote(control, history))
			return (0);
	}
	else
	{
		if (!(str = ft_strjoin_free(current_hist, control->term->line, 1)))
		{
			control->quit = 1;
			return (0);
		}
		history->head->content = str;
	}
	return (1);
}

/*
** note:	this function is in charge of appending the new input with the
**			current history line, in the case we reprompted because of an open
**			quote. therefore adding a '\n' in between the conctenation.
** RETURN:	1 ok
**			0 fialure, control->quit is raised
*/

int history_update_line_quote(t_control *control, t_history *history)
{
	char *str;

	str = (char *)(history->head->content);
	if (!(str = ft_strjoin_free(str, "\n", 1)))
	{
		control->quit = 1;
		return (0);
	}
	if (!(str = ft_strjoin_free(str, control->term->line, 1)))
	{
		control->quit = 1;
		free(str);
		return (0);
	}
	history->head->content = str;
	return (1);
}

/*
** note:	this function will decide if we discard the last link we created
**			and pushed at the front of the history linked list.
** note:	Discard occurs if the history->content is null, or contains an
**			empty string, or contains a string with white spaces only.
** note:	if the link is discarded: history->size--, and no need to process
**			to the lexer.
**
** return:	1 discard (set control->ctrl_c to 1)
**			0 OK
*/

int	history_decide_discard_new_link(t_control *control)
{
	char *str;
	int i;
	int len;

	str = (char *)(control->history->head->content);
	if (!str || !(len = ft_strlen(str)))
	{
		control->history->size--;
		ft_dlstpop_front(&control->history->head, history_del_content);
		control->ctrl_c = 1;
		return (1);
	}
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (i == len)
	{
		control->history->size--;
		ft_dlstpop_front(&control->history->head, history_del_content);
		control->ctrl_c = 1;
		return (1);
	}
	return (0);
}
