#include "minishell.h"

/*
** note:	when entering this function, we know that at the start index is a
**			valid assignement sign. whatever is behing could be subject to tild
**			expansion. tild that will be expanded need to be either directly
**			after the equal sign, or directly behind the potential ':'
**			separarting paths.
**
** note:	as we expand, the token's string gets directly updated.
**
** RETURN:	0 KO
**			1 OK
*/

int	expand_tild_in_assignement(char **str, char *home_env, int i, int start)
{
	int		esc_next;
	char	quoted;

	esc_next = 0;
	quoted = 0;
	while ((*str)[++i])
	{
		if ((i == start + 1) && !tild_expand_try(str, home_env, &i))
			return (0);
		if (!quoted && !esc_next && (*str)[i] == '\\')
		{
			esc_next = 1;
			continue;
		}
		if (!esc_next && ((*str)[i] == '\'' || (*str)[i] == '"'))
			path_set_quoted((*str)[i], &quoted);
		if (!quoted && !esc_next && (*str)[i] == ':')
		{
			if (!tild_expand_try_after_column(str, home_env, &i))
				return (0);
		}
		esc_next = 0;
	}
	return (1);
}

/*
** note:	this function is called when we are in the value part of an
**			assignement string, and a ':' is met (unquoted).
**
** note:	if the next character is a tild, we will expand it and update the
**			index.
**
** RETURN:	0 KO
**			1 OK
*/

int	tild_expand_try_after_column(char **str, char *home_env, int *i)
{
	if (!(*str)[*i + 1])
		return (1);
	(*i)++;
	if (is_tild_expandable(*str, *i))
		return (tild_expand_try(str, home_env, i));
	(*i)--;
	return (1);
}

