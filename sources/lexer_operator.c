#include "minishell.h"

/*
** this file is a subset of the lexer_root.c and lexer_find_token.c
** it is taking care of the case when an operator character is encountered:
**	operator we can encounter:
**	'&&', '||', '<<', '<', '>>', '>', '(', ')', '|', ';'
*/

/*
** note:	this function will be entered in the case we have met an operator
**			as a first characer for out token.
** RETURN:	1 ok
**			0 if malloc failed
*/

int	lexer_operator(const char *input, int *j, t_token *token)
{
	lexer_set_operator_id(token, input[*j]);
	if (input[*j] == ';')
	{
		*j += 1;
		if (!(token->str = ft_strdup(";")))
			return (0);
		return (1);
	}
	else if (input[*j] == '(')
	{
		*j += 1;
		if (!(token->str = ft_strdup("(")))
			return (0);
		return (1);
	}
	else if (input[*j] == ')')
	{
		*j += 1;
		if (!(token->str = ft_strdup(")")))
			return (0);
		return (1);
	}
	else if (!ft_stristr(input + *j, "<>&|"))
		return (lexer_operator2(input, j, token));
	return (0);
}

/*
** note:	this function takes care of the case when the operator is either
**			AND or OR ('&' or '|') , or a redirection symbol ('<'. '>')
**
** RETURN:	1
**			0 if malloc failed
*/

int	lexer_operator2(const char *input, int *j, t_token *token)
{
	char c;

	c = input[*j];
	if (!ft_append_char(&(token->str), c))
		return (0);
	(*j)++;
	if (!(input[*j]))
		return (1);
	else if (input[*j] == c)
	{
		token->id++;
		(*j)++;
		if (!ft_append_char(&(token->str), c))
			return (0);
	}
	return (1);
}

void	lexer_set_operator_id(t_token *token, char c)
{
	if (c == ';')
		token->id = SEMI;
	else if (c == '(')
		token->id = LBRACE;
	else if (c == ')')
		token->id = RBRACE;
	else if (c == '|')
		token->id = PIPE;
	else if (c == '&')
		token->id = AND;
	else if (c == '<')
		token->id = LESS;
	else if (c == '>')
		token->id = GREAT;
}
