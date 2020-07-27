#include "minishell.h"

/*
** this file will be in charge of trying to expand a token/its string if it
** contains an unquoted kleen star operator. one token can become multiple
** tokens in this stage of word expansion that sits between the parameter
** expansion and quote removal.
*/

/*
** note:	we are going to loop over each link of the linked list resulting
**			from the expansion of a token, and each time assess if the pathname
**			expansion should be done.
**			If yes, we build a new linked list from the expansion of the
**			link/token/string and replace it in situ.
**
** inputs:	token list, it is originally a list of one token, but the parameter
**				expansion could produce some more tokens if field splitting
**				occured.
**			is_filename.
**
** RETURN:	0, Ok
**			1, KO, ambiguous redirect
**			2, KO, fatal error
*/

int	pathname_expansion_root(t_list **tokens, int is_filename)
{
	int res;

	while (*tokens)
	{
		if (!pathname_is_expandable(((t_token*)(*tokens)->content)->str))
			quote_removal((t_token*)(*tokens)->content);
		else
		{
			if ((res = pathname_expansion(&tokens, is_filename)))
				return (res);
		}
		tokens = &(*tokens)->next;
	}
	return (0);
}

/*
** note:	for a given token and its string, we assess if yes or no we should
**			operate a pathname expansion, is there an unquoted kleen star
**			operator?
**
** RETURN:	1 yes
**			0, no
*/

int	pathname_is_expandable(char *str)
{
	int quoted;
	int	escaped;
	int i;

	quoted = 0;
	escaped = 0;
	i = 0;
	while (str[i])
	{
		if (!escaped && str[i] == '\\')
		{
			i++;
			escaped = 1;
			continue;
		}
		if (!escaped && !quoted && (str[i] == '\"' || str[i] == '\''))
			quoted = str[i];
		else if (!escaped && quoted && str[i] == quoted)
			quoted = 0;
		else if (!escaped && !quoted && str[i] == '*')
			return (1);
		escaped = 0;
		i++;
	}
	return (0);
}

/*
** note:	this function will expand the pathname of the given token.
**			the expansion goes into a new linked list.
**			if more than one token is created and filename is set an ambiguous
**			redirect message is displayed.
**			at the end the new linked list in inserted and replaces the current
**			token in the input linked list.
**
** inputs:	the adress of a token, needs to be replaced by the new linked list.
**			is_filename. used for ambiguous redirect warning.
**
** RETURN:	0, OK
**			1, KO, ambiguous redirect.
**			2, fatal error.
*/

int	pathname_expansion(t_list ***token, int is_filename)
{
	char *str;

	/* start the function that prepares the new struct here
	   look into file Miscellaneous/plan_path_exp.txt for instructions
	if (!(unquote_for_pathname_expansion((**token)->content)))
		return (2);
		*/
	str = ((t_token*)((**token)->content))->str;
	(void)token;
	(void)is_filename;
	(void)str;
	return (0);
}
