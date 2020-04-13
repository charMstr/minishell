#include "minishell.h"

/*
** this file is a subset of the lexer_root.c and lexer_find_token.c
** it is taking care of the case when a quoted string is encountered.
*/

/*
** note:	this function is called when we meet a first unquoted quote
**			character (' or ")
** note:	for the simple quote everything is taken literally (even '\').
**
** RETURN:	1 ok
**			0 if malloc failed.
*/

int	lexer_quoted(const char *input, int *j, t_token *token)
{
	char c;

	c = input[*j];
	if (!ft_strappend(&(token->str), c))
		return (0);
	(*j)++;
	token->open_quote = 1;
	if (c == '\'')
	{
		token->id = S_QUOTE;
		return (lexer_quoted_single(input, c, j, token));
	}
	else
	{
		token->id = D_QUOTE;
		return (lexer_quoted_double(input, c, j, token));
	}
}

/*
** note:	this function is called when the double quote character is met.
**			Either at the very beginning of the token, or after a few non
**			quoted simbols: exemple: hey"salut" -> 1 token
** note:	at this stage (tokenisation or lexing) we wont make disapear the
**			'\' characters. we will when doing the quote removal.
** RETURN:	1 ok
**			0 if malloc failed
*/

int lexer_quoted_double(const char *input, char c, int *j, t_token *token)
{
	while (input[*j])
	{
		if (!ft_strappend(&(token->str), input[*j]))
			return (0);
		if (!token->esc_next && input[*j] == '\\' && lexer_jump_esc(j, token))
			continue;
		else if (!token->esc_next && input[*j] == c)
		{
			(*j)++;
			token->open_quote = 0;
			return (1);
		}
		token->esc_next = 0;
		(*j)++;
	}
	return (1);
}

/*
** note:	This function is called when we meet non escaped single quote.
**			This can be the very begining of the token, or the continuation
**			exemple: echo salut'hey'
** note:	There cannot be nested single quotes.
** RETURN:	1 ok
**			NULL if malloc failed
*/

int	lexer_quoted_single(const char *input, char c, int *j, t_token *token)
{
	while (input[*j])
	{
		if (!ft_strappend(&(token->str), input[*j]))
			return (0);
		if (input[*j] == c)
		{
			(*j)++;
			token->open_quote = 0;
			return (1);
		}
		(*j)++;
	}
	return (1);
}
