#include "minishell.h"

/*
** this file is a subset of the lexer_root.c and lexer_find_token.c
** it is taking care of the case when the token starts by anything expect for
** an operator or a quotation mark (or it can be an escaped one).
*/

/*
** note:	this function is going to be called when the token is neither going
**			to be an operator or a quote.
** RETURN:	1 ok
**			0 if malloc failed.
*/

int lexer_just_token(const char *input, int *j, t_token *token)
{
	while (input[*j] && (token->esc_next || input[*j] != ' '))
	{
		if (!token->esc_next)
		{
			if (input[*j] == '\\' && lexer_jump_esc(j, token))
				continue;
			else if (ft_strchr("\"\'", input[*j]))
				return (lexer_quoted(input, j, token));
			else if (ft_strchr("&<>()|;", input[*j]))
				return (1);
		}
		if (!ft_append_char(&(token->str), input[*j]))
			return (0);
		token->esc_next = 0;
		(*j)++;
	}
	return (1);
}

/*
** note:	this function is called when the first character of the token is a
**			number. it could possibly be part of an indirection as in the
**			formulas: [n]<word OR [n]>word OR [n]>>word ...
**
** RETURN:	1 ok
**			0 if failure in malloc
*/

int	lexer_token_or_indirection(const char *input, int *j, t_token *token)
{
	while (ft_isdigit(input[*j]))
	{
		if (!ft_append_char(&(token->str), input[*j]))
			return (0);
		(*j)++;
	}
	if (input[*j] && input[*j] != ' ')
	{
		if (ft_strchr("&()|;", input[*j]))
			return (1);
		else if (ft_strchr("<>", input[*j]))
			return (lexer_indirection(input, j, token));
		else
			return (lexer_just_token(input, j, token));
	}
	return (1);
}

/*
** note:	this function is going to be called when we the beginning of the
**			token with only numbers (not even an escape sequence!) and the
**			current character is either '<' or '>' so we are in the case of an
**			indirection token.
** RETURN:	1 ok
**			0 if failure
*/

int	lexer_indirection(const char *input, int *j, t_token *token)
{
	if (input[*j] == '<')
		token->id = LESS;
	else
		token->id = GREAT;
	return (lexer_operator2(input, j, token));
}
