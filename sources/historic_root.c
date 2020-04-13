#include "minishell.h"

/*
** this file is in charge of the historic, implemented through a bidirectional
** linked list.
*/

/*
** note:	function to init the history stucture in control.
**
** RETURN:	t_history *
**			NULL if failure
*/

t_history *history_init_struct(void)
{
	t_history *hist;

	if (!(hist = (t_history*)malloc(sizeof(t_history))))
		return (NULL);
	hist->size = 0;
	hist->max_size = 255;
	hist->head = NULL;
	return (hist);
}

/*
** note:	this function will clean a link from the linked list history->head
*/

void	history_del_content(void *content)
{
	char *str;

	str = (char *)content;
	free(str);
}

/*
**  note:	this function will creat a new link link in the history and push it
**			to the front.
** note:	control->history->size is bigger than control->history->max_size,
**			then end of the list is trimed.
**
** RETURN:	0 if failure
**			1 ok
*/

int history_add_new_link(t_control *control)
{
	t_dlist *history_new;

	char *str;

	if (!(str = ft_strdup("")))
	{
		control->quit = 1;
		return (0);
	}
	if (!(history_new = ft_dlstnew(str)))
	{
		free(str);
		control->quit = 1;
		return (0);
	}
	ft_dlstadd_front(&(control->history->head), history_new);
	control->history->size++;
	if (control->history->size > control->history->max_size)
	{
		control->history->size--;
		ft_dlstpop_back(&control->history->head, history_del_content);
	}
	return (1);
}

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
