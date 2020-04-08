#include "minishell.h"

/*
** this file will be in charge of the parsing, step that come after	the lexer
** (the tokenisation is done).
*/

/*
** note:	this function is the root_function of the parsing for the command
**			line that went through the lexer
**
** RETURN:	t_parser *
**			NULL malloc failed
*/

//t_parser	*

/*
** note:	this function will take the data collected into the tokens linked
**			list and fill a simple command structure.
** RETURN:	a s_cmd structure
*/

t_simple_command *parser_simple_cmd(t_list *lex)
{
	t_simple_command *s_cmd;

	(void)lex;
	s_cmd = NULL;
	return (s_cmd);
}

