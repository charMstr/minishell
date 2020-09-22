#include "minishell.h"

/*
** this file is the root file for the pathname expansion:
**		ex: y* -> yo.txt yeah.txt yes.txt
**
** we initially had a simple command. we choose one token and started expansion
** which resulted in a temporary linked list (multiple tokens could have
** resulted from  word expansion with field splitting).
** We will loop over this linked list and for each token assess if it contains
** at least one unquoted kleen star operator (it means pathname is expandable).
** If not we just call the quote removal function.
** If yes, the string is unquoted somehow, then either:
**			- no matches with filenames. the unquoted version of the token is
**				replacing itself in the list.
**			- at least one match. the new linked list in inserted in place as
**				well.
**			- more than one. do as above but need to make sure we are not in
**				the case of a filename replacement, otherwise error message is
**				displayed.
*/

/*
** note:	we are going to loop over each link of the linked list resulting
**			from the stage1 expansion of a token (ie. after word expansion and
**			field splitting), and each time assess if the pathname
**			expansion should be done.
**			If yes, we build a new linked list from the expansion of the
**			link/token/string and replace it in situ.
**
** inputs:	- token list.
**			- is_filename.
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
** note:	this function will expand the pathname with the starting point
**			of the current token. this current token isnt modified until the
**			end. Either we succeffully created a new list of tokens containing
**			new	path-names, we therefor replace the original token with those
**			new filesnames. Or no filename matched and we simply unquote the
**			original token.
** note:	If more than one token is created and is_filename is 1 an ambiguous
**			redirect message is displayed.
**
** note:	we are going to creat a structure containing all the material
**			for pathname_expansion.
**			then we will call a recursive function that will attempt to
**			build a linked list of filenames (pathnames) as it goes.
**
** inputs:	- the token adress, needs to be replaced by the new linked list.
**				3 stars so we can update the adress in the loop that called
**				this function.
**			is_filename. used for ambiguous redirect warnings...
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
	//need to work on something else than the real string.
	str = ((t_token*)((**token)->content))->str;
	printf("str is: %s\n", str);
	collapse_fwd_slashes(str, 0, -1, 0);
	printf("str2 is: %s\n", str);
	split_path_root(str);
	return (0);
}

/*
** note:	this function will collapse all the mutltiple consecutive forward
**			slashes into one, exception if they are escapsed.
**			only single or double quotes can be in the middle of two
**			consecutive forward slashes.
**
** input:	str, string that may contain multiple successive '/'
**			esc_next, initially set to 0.
**			i and k, set to 0.
*/

void collapse_fwd_slashes(char *str, int esc_next, int i, int k)
{
	while (str[++i])
	{
		if (str[i] == '\\' && esc_next == 0)
		{
			esc_next = 1;
			continue;
		}
		if (esc_next != 1 && str[i] == '/')
		{
			k = i;
			while (str[++k])
			{
				if (str[k] != '/' && str[k] != '"' && str[k] != '\'')
				{
					i = k - 1;
					break;
				}
				if (str[k] == '/')
					ft_strcdel(str, k--);
			}
		}
		esc_next = 0;
	}
}
