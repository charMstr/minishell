#include "minishell.h"

/*
** this file is in charge of the historic, implemented through a bidirectional
** linked list.
*/

/*
** note:	this function is the root function for updatng the history after
**			each prompt
**
** note:	if zero is returned. flags are being raise daccordingly:
**			- control->quit to exit the program
**			- control->ctrl_c if line and history->head->line are both empty
**				in that case the current histoy link is discarded.
**
** RETURN:	1 ok keep goin, enter lexer_root()
**			0 stop
*/

int		history_root(t_control *control, t_history *history)
{
	if (!control->term->line)
	{
		if (!(control->term->line = ft_strdup("")))
		{
			control->quit = 1;
			return (0);
		}
	}
	if (!history_update_line(control, history))
		return (0);
	if (history_decide_discard_new_link(control))
		return (0);
//	debug_history_list(control->history)
	return (1);
}

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
