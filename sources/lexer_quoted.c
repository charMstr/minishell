#include "minishell.h"

/*
** this file is a subset of the lexer_root.c and lexer_find_token.c
** it is taking care of the case when a quoted string is encountered.
*/

/*
** note:	this function is called when we meet a first unquoted quote
**			character (' or ")
**
** RETURN:	1 ok
**			0 if malloc failed.
*/

int	lexer_quoted(const char *input, int *j, t_token *token)
{
	char c;

	c = input[*j];
	token->open_quote = 1;
	token->id = (c == '\"') ? D_QUOT : S_QUOT;
	if (!ft_append_char(&(token->str), c))
		return (0);
	(*j)++;
	while (input[*j])
	{
		if (!token->esc_next && input[*j] == '\\' && lexer_jump_esc(j, token))
			continue;
		else if (!ft_append_char(&(token->str), input[*j]))
			return (0);
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
