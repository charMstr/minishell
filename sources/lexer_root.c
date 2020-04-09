#include "minishell.h"

/*
** this file is the root file for the first step of the parsing: tokenising.
** the tokenisation is going to be a linked list of t_token elements.
*/

/*
** note:	this func is the root func for the tokenisation.
** input:	a string that cannot be null or empty or only containing
**			whitespaces: the raw command line.
** RETURN:	a linked list containing t_token struct.
**			NULL if a malloc failed.
*/

//The <backslash> and <newline> shall be removed before splitting the input into tokens.
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
			ft_lstclear(&tokens_head, del_token);
			return (NULL);
		}
		if (!(tokens_elem = ft_lstnew(new_token)))
		{
			ft_lstclear(&tokens_head, del_token);
			return (NULL);
		}
		ft_lstadd_back(&tokens_head, tokens_elem);
		//debug_token_struct(new_token);
	}
	//debug_tokens_list(tokens_head);
	return (tokens_head);
}

/*
** note:	this function will be called when destroying the linked list
**			containing token
*/

void	del_token(void *token)
{
	free(((t_token *)(token))->str);
	free((t_token*)token);
}

/*
** note:	This function will retUrn the next token lexed from the raw string
**			and update the index we are at in the string.
** note:	if the token returned has a NULL str. it means the portion of the
**			command contained spaces only until the EOL.
** input:	The base address of the string.
**			The index we are at in the string (updated by address)
**
** RETURN:	The structure containing the next token
**			NULL if malloc failed
*/

t_token	*lexer_build_next_token(const char *input, int *j)
{
	t_token		*token;

	if (!(token = lexer_init_token()))
		return (NULL);
	while (input[*j] && input[*j] == ' ')
		(*j)++;
	if (!input[*j])
		return (token);
	if (!(lexer_find_token(input, j, token)))
	{
		free(token);
		return (NULL);
	}
	return (token);
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
	token->esc_next = 0;
	token->open_quote = 0;
	token->id = 0;
	return (token);
}
