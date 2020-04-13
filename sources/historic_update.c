#include "minishell.h"

/*
** this file is in charge of updateing the historic, deciding how to add the
** line we got from the prompt to the current link. and deciding if we keep or
** discard that link.
*/

/*
** note:	this function will take care of adding the line we just got from
**			the user's input to the current history's head link content.
** note:	Do not free control->term->line here. it is done at the end of each
**			prompt loop.
**
** RETURN:	1 ok
**			0 failure (the control->quit flag will be raised as well)
*/

//for now just just append to history dumbly. but refer to fow-chart diagram.

int	history_append_line(t_control *control, t_history *history)
{
	char *new;

	if (!control->term->line)
		return (1);
	if (!(new = ft_strjoin((char*)(history->head->content), \
					control->term->line)))
	{
		control->quit = 1;
		return (0);
	}
	free((char*)(history->head->content));
	history->head->content = new;
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
