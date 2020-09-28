/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tild_expansion_root.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 10:50:15 by mli               #+#    #+#             */
/*   Updated: 2020/09/28 10:51:25 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file is in charge of a basic tild expansion
** we will just take care of the most basic unquoted '~' followed by a
** '/' or nothing. note that the tild expansion is realised before the
** parameter expansion while processing all the word expansions.
*/

/*
** note:	this function will try to assess if the token's string is either an
**			assignement or a path starting by a tild.
**			depending of the assessment the tild expansion is operated
**			differently.
**
** note:	we consider that if the HOME env variable is unset, we just
**			don't expand the tild.
**
** input:	str, the address of the string contained in the token.
**			env, used to get the login home directory.
**
** RETURN:	0 KO
**			1 OK
*/

int	tild_expansion_root(t_list *env, char **str)
{
	char	*home_env;
	int		start_assignement;
	int		index;

	index = 0;
	if (!(home_env = env_get("HOME", 4, env)))
		return (1);
	start_assignement = index_assignement_sign(*str);
	if (start_assignement == -1)
		return (tild_expand_try(str, home_env, &index));
	else
		return (expand_tild_in_assignement(str, home_env, start_assignement, \
				start_assignement));
}

/*
** note:	this function will assess if the tild is expandable and expand it
**
** RETURN:	0 KO
**			1 OK
*/

int	tild_expand_try(char **str, char *home_env, int *i)
{
	int res;

	if (!is_tild_expandable(*str, *i))
		return (1);
	ft_strcdel(*str, *i);
	res = ft_strstradd(str, *i, home_env);
	if (res)
		*i = *i + ft_strlen(home_env);
	return (res);
}

/*
** note:	this function will try to see if the very first character of the
**			string is an unquoted '~', and if it is followed either by nothing
**			or a '/'.
**
** return:	1 OK, expandable.
**			0 KO.
*/

int	is_tild_expandable(char *str, int i)
{
	if (!str[i])
		return (0);
	if (str[i] != '~')
		return (0);
	i++;
	if (!str[i] || str[i] == '/' || str[i] == ':')
		return (1);
	return (0);
}

/*
** note:	this function will check if we are in the context of an assignement
**			we are basically looking for a '=' sign in the token's string.
**
** note:	the label figuring before the first '=' sign need to start with
**			an alphabetic symbol and be composed of only alphanumeric char.
**			therefore any quoting character or a string starting just by a '='
**			is not a valid assignement
**
** RETURN:	index of the valid '='.
**			-1 otherwise.
*/

int	index_assignement_sign(char *str)
{
	int i;

	i = 1;
	if (!str[0] || !ft_isalpha(str[0]))
		return (-1);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		if (!(ft_isalpha(str[i])))
			return (-1);
		i++;
	}
	return (-1);
}
