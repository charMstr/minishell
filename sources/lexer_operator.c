#include "minishell.h"

/*
** this file is a subset of the lexer_root.c and lexer_find_token.c
** it is taking care of the case when an operator character is encountered:
**	operator we can encounter:
**	'&&', '||', '<<', '<', '>>', '>', '(', ')', '|', ';'
*/

/*
** note:	this function will be entered in the case we have met an operator.
**			If we were currently building a token, we can detect it with
**			token->str being non NULL. we terminate the current token.
**
** RETURN:	1 ok
**			0 if malloc failed
*/

int	lexer_operator(const char *input, int *j, t_token *token)
{
	if (token->str)
		return (1);
	lexer_set_operator_id(token, input[*j]);
	if (ft_strchr("();", input[*j]))
	{
		(*j)++;
		if (!(token->str = ft_strdup((char [2]){input[*j - 1], '\0'})))
			return (0);
		return (1);
	}
	else if (ft_strchr("<>&|", input[*j]))
		return (lexer_operator2(input, j, token));
	return (0);
}

/*
** note:	this function takes care of the case when the operator is either
**			AND or OR ('&' or '|') , or a redirection symbol ('<'. '>')
**			and '&&', '||', '<<', '>>'.
**
** RETURN:	1
**			0 if malloc failed
*/

int	lexer_operator2(const char *input, int *j, t_token *token)
{
	char c;

	c = input[*j];
	if (!ft_strappend(&(token->str), c))
		return (0);
	(*j)++;
	if (input[*j] == c)
	{
		token->id++;
		(*j)++;
		if (!ft_strappend(&(token->str), c))
			return (0);
	}
	return (1);
}

void	lexer_set_operator_id(t_token *token, char c)
{
	int			i;
	const char	op_ids[][2] = (const char [][2]){{'(', LBRACE}, {')', RBRACE},
	{'|', PIPE}, {'&', AND}, {';', SEMI}, {'<', LESS}, {'>', GREAT}, {0, 0}};

	i = -1;
	while (op_ids[++i][0])
		if (op_ids[i][0] == c)
			token->id = op_ids[i][1];
}
