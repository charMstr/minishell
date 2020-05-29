#include "minishell.h"

/*
** note:	at this stage, we already commited to field splitting, since the
**			array contains at least two strings. We will have to malloc at
**			least one new token and append it to the string.
**			current token's string is actually str1, and the second part str2
**			is given as a parameter.
**			the first field is appended to the end of str1 in the current token
**			And the other fields go into newly created and appended tokens.
**			str2 is appended to the last token.
**
** note:	when tokens are created/appended, the token variable is shifted to
**			next. In that case also the start is updated.
**
** input:	-array: the expanded parameter that got field split.
**			-token: in which is str1, in which we will inject var's first field
**			-exp: the structure containg start, which need to be updated.
**			-str2: will be appended to the last token.(could be the first one
**			if no splitting occurs.
**
** RETURN:	1 OK
**			0 KO
*/

int	field_splitting(t_list ***tok, t_expansion *exp, char **array, char *str2)
{
	char **str;
	int	i;

	i = 1;
	str = &((t_token*)(**tok)->content)->str;
	if (array[0] && !(*str = ft_strjoin_free(*str, array[0], 1)))
		return (0);
	while (array[i])
	{
		*tok = &(**tok)->next;
		if (!(field_splitting_assist(*tok, array[i])))
			return (0);
		i++;
	}
	str = &((t_token*)(**tok)->content)->str;
	exp->start = ft_strlen(*str);
	if (!(*str = ft_strjoin_free(*str, str2, 1)))
		return (0);
	return (1);
}

/*
** note:	this function receives the string that needs to be added into a new
**			token, creates the token for it and inserts it inplace in the token
**			list. We set the token->id to TOKEN for being clean.
**
** return:	1 OK
**			0 KO
*/

int	field_splitting_assist(t_list **tok, char *str)
{
	t_list *new_link;
	t_token *new_token;

	if (!(new_token = lexer_init_token()))
		return (0);
	if (!(new_token->str = ft_strdup(str)))
	{
		free(new_token);
		return (0);
	}
	new_token->id = TOKEN;
	new_token->unquote_protected = 1;
	new_token->protect_s = 0;
	new_token->protect_e = ft_strlen(new_token->str);
	if (!(new_link = ft_lstnew(new_token)))
	{
		del_token(new_token);
		return (0);
	}
	ft_lstadd_front(tok, new_link);
	return (1);
}
