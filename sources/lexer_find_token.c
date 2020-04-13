#include "minishell.h"

/*
** this file assists the lexer_root.c file, it takes care of delimiting the
** next token from the raw input line (from lezt to right).
*/

/*
** note:	This function will allocate memory for the token->str element of
**			token struct.
** note:	When starting we know that the first cahracter will be a character
**			other than end of string or space.
** note:	if the element token->esc_next is sitll on when we are done, it
**			means that the last char was a single escape sequence. this flag
**			should be carried upwards so that we can prompt a PS2.
**			same goes for tooken->open_quote...
** intput:	The raw input string.
**			The index we are at in this string.
**			The token struct.
**
** RETURN:	0 if failure in malloc
**			1
*/

int	lexer_find_token(const char *input, int *j, t_token *token)
{
	if (!token->esc_next)
	{
		if (input[*j] == '\\' && lexer_jump_esc(j, token))
			return (lexer_find_token(input, j, token));
		else if (ft_strchr("\"\'", input[*j]))
			return (lexer_quoted(input, j, token));
		else if (ft_strchr("&<>()|;", input[*j]))
			return (lexer_operator(input, j, token));
		else if (ft_isdigit(input[*j]))
			return (lexer_token_or_indirection(input, j, token));
	}
	return (lexer_just_token(input, j, token));
}

/*
** note:	this function will update the position in the string so that we can
**			jump to the next character in the case we meet an escape char '\'.
**
** RETURN:	1
*/

int	lexer_jump_esc(int *j, t_token *token)
{
	*j += 1;
	token->esc_next = 1;
	return (1);
}
