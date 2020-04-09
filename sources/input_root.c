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
	control->index_in_history = 0;

	//create a new link at the front of history linked list
	//if we reach history limit (ex: 255) we can pop end of list.
	//input_history_creat_link();

	//function where evetything happens
	tokens_lst = input_root_assist_and_prompt(control);

	//decide if we keep the link in history: not if in the current history link
	//the string is empty.
	//input_history_decide_for_link();
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

	//reset some controls values.
	control->ctrl_c = 0;
	//here we can recheck the values of ps1 and ps2 (in case they hace been
	//changed) and as well update the terminal size, all that in the
	//control->term struct
	while (!control->quit && !control->ctrl_c) //here we should check values in control structure
	{
		if (control->first_time)
			ft_putstr_fd(control->term->ps1, 2);
		else
			ft_putstr_fd(control->term->ps2, 2);
		terminfo_get_prompt_len(control);
	//	debug_term_struct(control->term);
		control->term->inline_position = 0;

		tokens_lst = input_reading_and_lexing(control);
		control->first_time = 0;
		//if lexer/tokenizer function worked: we would set ctrl_c to 1
		control->ctrl_c = 1;
	//	reset the line to NULL after each loop, even betwen PS1 and PS2
		ft_free((void **)&(control->term->line));
	}
	return (tokens_lst);
}

/*
** note:	this function will take care of the following maini tasks:
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
	t_list *tokens_lst;

	tokens_lst = NULL;
	//this function will edit line-->> might be appended to the current history
	// return in 4 situations:
	// malloc failed, ctrl_C, ctrl_D(empty string), 'ENTER KEY'
	control->term->line_len = 0;
	read_root(control, 0, 0);
	ft_putchar_fd('\n', 1);
/*
	// checking the control structure against ctrl_C, or Malloc_failure etc...
	if (input_check_for_return())
		return (NULL);
	//the line we need to process is situated in control->term->line
	//it will be appended to the current line history.
	input_check_multiline_and_update_history();
	if (input_check_for_return())
		return (...);
	//the thing we need to process is the whole current line history.
	// for now: just take a simple line. from control->term->line
*/
	if (!control->term->line)
		return (NULL);
	else
		printf("%s\n", control->term->line);
	tokens_lst = lexer_root(control->term->line);
/*
	if (input_check_for_return())
		return (...);
*/
	return (tokens_lst);
}
