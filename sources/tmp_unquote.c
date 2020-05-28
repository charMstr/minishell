#include "minishell.h"

/*
** note:	this function will unquote the redirections's filenames in the
**			t_simple_cmd struct's redirections and indirections.
*/

void	simple_cmd_unquote_redirections(t_simple_cmd *cmd)
{
	t_list	*tmp;

	tmp = cmd->redirections;
	while (tmp)
	{
		unquote_str(((t_arrow*)tmp->content)->filename);
		tmp = tmp->next;
	}
	tmp = cmd->indirections;
	while (tmp)
	{
		unquote_str(((t_arrow*)tmp->content)->filename);
		tmp = tmp->next;
	}
}

/*
**	note:	this function will shift all the characters to the left, and
**			replace the last quote by a '\0'. no mallocs.
** note:	the reduce_backslash function is called only if the quote_type is
**			double quote.
*/

void	unquote_str(char *str)
{
	int i;
	char quote_type;

	i = 0;
	if (!str || (str[0] != '\'' && str[0] != '\"'))
		return ;
	if (str[0] == '\'')
		quote_type = '\'';
	else
		quote_type = '\"';
	while (str[i])
	{
		if (quote_type == '\"' && str[i] == '\\' && str[i + 1] == '\\')
			reduce_backslash(str + i);
		i++;
	}
	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		if (!str[i])
			str[i - 1] = '\0';
		i++;
	}
}

/*
** note:	This function is called when removing the quotes from a string
**			if we have a double back_slash, it is reduced to one backslash.
**			Whatever that was on the right is shifted to the left one index
**			magnitude.
*/

void	reduce_backslash(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}
