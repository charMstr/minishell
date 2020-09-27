#include "minishell.h"

/*
** this file is in charge of a basic tild expansion
** we will just take care of the most basic unquoted '~' followed by a
** '/'.
*/


/*
** note:	this function will replace the first tild with the $HOME
**			env variable if possible.
**
** note:	we consider that if the HOME env variable is unset, we just
**			don't expand the tild.
**
** input:	str, the address of the string contained in the token.
**
** RETURN:	0 KO
**			1 OK
*/

int	tild_expansion_root(t_list *env, char **str)
{
	char *home_env;

	if (!is_tild_expandable(*str))
		return (1);
	ft_strcdel(*str, 0);
	if (!(home_env = env_get("HOME", 4, env)))
		return (1);
	return (ft_strstradd(str, 0, home_env));
}

/*
** note:	this function will try to see if the very first character
**			of the string is an unquoted '~', and if it is followed
**			either by nothing or a '/'.
** return:	1 OK, expandable.
**			0 KO.
*/

int		is_tild_expandable(char *str)
{
	int i;

	i = 0;
	if (str[i] != '~')
		return (0);
	i++;
	if (!str[i] || str[i] == '/')
		return (1);
	return (0);
}
