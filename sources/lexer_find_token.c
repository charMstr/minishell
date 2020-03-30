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
	if (!token->esc_next && input[*j] == '\\' && lexer_jump_esc(j, token))
		return (lexer_find_token(input, j, token));
	else if (!token->esc_next && !ft_stristr(input + *j, "\"\'"))
		return (lexer_quoted(input, j, token));
	else if (!token->esc_next && !ft_stristr(input + *j, "&<>()|;"))
		return (lexer_operator(input, j, token));
	else if (!token->esc_next && ft_isdigit(input[*j]))
		return (lexer_token_or_indirection(input, j, token));
	else
		return (lexer_just_token(input, j, token));
	return (0);
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

/*
** note:	this function will append a char to a string that does not need to
**			be existing. the string is updated and memory of the old string is
**			freed anyway.
**
** RETURN:	1 if OK
**			0 elsewise.
*/

int	ft_append_char(char **str, char c)
{
	char *char_str;
	char *old;

	old = *str;
	if (!(char_str = (char *)malloc(sizeof(char) * 2)))
		return (0);
	char_str[0] = c;
	char_str[1] = '\0';
	if (!*str)
	{
		*str = char_str;
		return (1);
	}
	else
	{
		*str = ft_strjoin(old, char_str);
		free(old);
		free(char_str);
		if (!(*str))
			return (0);
		return (1);
	}
}
