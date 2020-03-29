#include "minishell.h"

/*
** this file is the root file for the first step of the parsing: tokenising.
** the tokenisation is going to be a linked list of t_token elements.
*/

/*
** note:	this func is the root func for the tokenisation.
** input:	a string that cannot be null(the raw command line).
** RETURN:	a linked list containing t_token struct.
**			NULL if a malloc failed.
*/

t_list	*lexer_root(char *input)
{
	t_list	*tokens_head;
	t_list	*tokens_elem;
	t_token	*new_token;
	int		i;

	i = 0;
	tokens_elem = NULL;
	tokens_head = NULL;
	while (input[i])
	{
		if (!(new_token = lexer_build_next_token(input, &i)))
		{
			//destroy linked list
			return (NULL);
		}
		if (!(tokens_elem = ft_lstnew(new_token)))
		{
			//destroy linked list
			return (NULL);
		}
		ft_lstadd_back(&tokens_head, tokens_elem);
	}
	debug_tokens_list(tokens_head);
	return (tokens_head);
}

/*
** note:	This function will NOPENOPENOPE the next token in the raw string
**			and update the index we are at in the string.
** note:	if the token returned has an empty str. it means the portion of the
**			command contained spaces only until the EOL.
** input:	The base address of the string, whick will be updated by address.
**			The index we are at in the string
**
** RETURN:	The structure containing the next token, to be added to the linked
**			list of tokens.
**			NULL if malloc failed
*/

t_token	*lexer_build_next_token(const char *input, int *j)
{
	t_token		*token;
	t_lexing	lex;
	char		*token_str;

	lexer_init_lexing_struct(&lex);
	if (!(token = lexer_init_token()))
		return (NULL);
	while (input[*j] && input[*j] == ' ')
		(*j)++;
	if (!input[*j])
		return (token);
	if (!(token_str = lexer_find_token(input, j, lex)))
	{
		free(token);
		return (NULL);
	}
	token->str = token_str;
	return (token);
}

/*
** note:	this function will initialise the parsing struct build_token.
*/

void	lexer_init_lexing_struct(t_lexing *lex)
{
	lex->operator = 0;
	lex->empty = 1;
	lex->s_quoted = 0;
	lex->d_quoted = 0;
	lex->esc_next = 0;
	lex->is_alpha = 0;
	lex->is_num = 0;
}

/*
** note:	This function will allocate memory for the next token_str/lexem
** note:	We starting we know that the first cahracter will be a character
**			other than end of string or space.
** intput:	The raw input string.
**			The index we are at in this string.
**			The lexing struct helping us to identify the end of the token_str
**
** RETURN:	NULL if failure in malloc
**			token_str, that will go in the token->str element.
*/

char	*lexer_find_token(const char *input, int *j, t_lexing lex)
{
	char *token_str;
	char *new;

	token_str = NULL;
	while (input[*j] && input[*j] != ' ')
	{
		//if quote
		//return ();
		//RESTART HERE
		lexer_update_lexing_struct(input[*j], &lex);
		if (!ft_stristr(input + *j, "&<->()|;"))
			return (lexer_operator(input, token_str, j, &lex));
		new = ft_stradd_char(token_str, input[*j]);
		free(token_str);
		token_str = new;
		if (!new)
			return (NULL);
		lex.empty = 0;
		(*j)++;
	}
	debug_lexing_struct(&lex);
	return (token_str);
}

/*
** note:	this function will keep the flags updated in the structure helping
**			with the tokenisation, according to each new char we encounter.
*/

void	lexer_update_lexing_struct(char c, t_lexing *lex)
{
	if (ft_isalpha(c))
		lex->is_alpha = 1;
	else if (ft_isdigit(c))
		lex->is_num = 1;
	else if (c == '\\')
		lex->esc_next = 1;
}
/*
** note:	this function will be entered in the case we have met an operator
**			according to grammar.
** note:	2 cases:	- we had some characters before
**						subcases:	- they were only numeric so far and we have
**									a redirection, we keep on if the operator
**									is a redirection operator
**									- they were not. we stop right now
**						- first char of the lexem is an operator
**
** RETURN:	string.
**			NULL if malloc failed
*/

/*
** operator we can encounter:
**	'&&', '||', '<<', '<', '>>', '>', '(', ')', '|', ';'
*/

char *lexer_operator(const char *input, char *token_str, int *j, t_lexing *lex)
{
	char *str;

	token_str = (char *)token_str;
	str = NULL;
	if (lex->empty)
	{
		*j += 1;
		if (input[*j - 1] == ';')
			return (ft_strdup(";"));
		else if (input[*j - 1] == '(')
			return (ft_strdup("("));
		else if (input[*j - 1] == ')')
			return (ft_strdup(")"));
	}
	debug_lexing_struct(lex);
	return (str);
}

/*
** note:	this function will append a char to a string that does not need to
**			be existing.
**
** RETURN:	NULL if malloc failure
**			str + char
*/

char *ft_stradd_char(char *str, char c)
{
	char *new;
	char *char_str;

	if (!(char_str = (char *)malloc(sizeof(char) * 2)))
		return (NULL);
	char_str[0] = c;
	char_str[1] = '\0';
	if (!str)
		return (char_str);
	else
	{
		new = ft_strjoin(str, char_str);
		free(char_str);
		return (new);
	}
}

/*
** note:	this function will init the token struct
** note:	the str will be initiated to NULL
**
** RETURN:	NULL if failed Malloc.
**			a token struct
*/

t_token	*lexer_init_token(void)
{
	t_token *token;
	if (!(token = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	token->str = NULL;
	//set all the the elements in token to zero.
	return (token);
}
