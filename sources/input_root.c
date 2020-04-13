#include "minishell.h"

/*
** note:	this function is the root function for geting the user input before
**			passing it to the parser.
**
** note:	returning NULL doesnt mean we have to quit the program, it could be
**			because we simply pressed ctrl_C, sowe will rather use a control
**			structure with flags for that.
**
** RETURN:	a linked list of the tokens
**			NULL
*/

t_list *input_root(t_control *control)
{
	t_list *tokens_lst;

	control->first_time = 1;
	if (!history_add_new_link(control))
		return (NULL);
	//function where evetything happens
	tokens_lst = input_root_assist_and_prompt(control);
	if (control->quit)
		return (NULL);
	return (tokens_lst);
}

/*
** note:	this function should do the majority of the job getting the user
**			input
** note:	as above, returning NULL, doesnt mean we have to quit, we rather
**			use flags for this purpose in a control struct
**
** RETURN:	t_tokens_lst*
**			NULL
*/

t_list *input_root_assist_and_prompt(t_control *control)
{
	t_list *tokens_lst;

	control->ctrl_c = 0;
	//here we can recheck the values of ps1 and ps2 in case they have been
	//changed with export and as well update the terminal size, all that in the
	//control->term struct
	while (!control->quit && !control->ctrl_c)
	{
		if (control->first_time)
			ft_putstr_fd(control->term->ps1, 2);
		else
			ft_putstr_fd(control->term->ps2, 2);
		if (!input_reset_term_struct(control))
			return (NULL);
		// if the tokens_lst is null, it means we need to reprompt. OK
		// if an error occured(malloc failing) control->quit should be reaised.
		tokens_lst = input_reading_and_lexing(control);
		control->first_time = 0;
		//if lexer/tokenizer function worked: it would set ctrl_c to 1
		// leave ctrl_c to 0 and you see PS2 appearing (we stay in the loop)
		control->ctrl_c = 1;
	//	reset the line to NULL after each loop, even betwen PS1 and PS2
		ft_free((void **)&(control->term->line));
	}
	return (tokens_lst);
}

/*
** note:	this function is in charge of reseting the control->term fields
**			each time we restart afresh with a new prompt.
**
** RETURN:	1 ok
**			0 failure
*/

int	input_reset_term_struct(t_control *control)
{
	if (!terminfo_cursor_get_pos(control, &(control->term->cursor_start)))
		return (0);
	control->term->cursor = control->term->cursor_start;
	control->term->prompt_len = control->term->cursor.x;
	control->term->inline_position = -1;
	control->term->line_len = 0;
	control->term->current_history_link = control->history->head;
	return (1);
}

/*
** note:	this function will take care of the following main tasks:
**			-	read and append characters.
**			-	update control structure
**			-	check if a line ends with a '\'
**			-	update the curent history link
**			-	send the full content of the history link to the lexer.
**
** RETURN:	t_token_list *
**			NULL
*/

t_list *input_reading_and_lexing(t_control *control)
{
	t_list *token_lst;

	token_lst = NULL;
	read_root(control, 0, 0);
	if (!terminfo_cursor_move_endl(control, 0))
		return (NULL);
	ft_putchar_fd('\n', 1);
	if (!input_check_for_stop_condition(control))
		return (NULL);
	// ne pas free line la dedans!!!
	// this function will need more granularity/subfunctions depending
	//on the previous returns of the flag.
	if (!history_append_line(control, control->history))
		return (NULL);
	//if (we decide to discard the hist no need to go to the lexer
	if (history_decide_discard_new_link(control))
		return (NULL);
//	debug_history_list(control->history);
	printf("ENTERING LEXER WITH: [%s]\n", control->history->head->content);
	token_lst = lexer_root((char *)(control->history->head->content), control);
	return (token_lst);
}

/*
** note:	this function will catch the raised flags
**
** RETURN:	1 ok
**			0 either crl_c or quit was raised
*/

int	input_check_for_stop_condition(t_control *control)
{
	if (control->quit || control->ctrl_c)
		return (0);
	return (1);
}
