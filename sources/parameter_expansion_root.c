/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_root.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:25:39 by mli               #+#    #+#             */
/*   Updated: 2020/09/28 09:54:34 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** This file is in charge of the parameter expansion, first stage of the word
** expansion.  example "hey salut $TOI" -> "hey salut charlie"
** Field splitting occurs at this stage, therefor a single token can produce
** multiple tokens.
*/

/*
** note:	this function will update the linked list of token, we start with
**			a linked list containing one single token, the word to expand,
**			we replace the $VAR, and create new tokens if some field splitting
**			should occur. In that case, a new token is created for each field
**			separation, and inserted in place into the linked list.
**
** RETURN:	0 OK
**			1, ambiguous redirect (only if is_filename is true)
**			2, fatal error.
*/

int		parameter_expansion_root(t_list *token, \
		t_control *control, int filename)
{
	t_expansion	exp;
	int			res;

	res = 0;
	reset_t_expansion(&exp, filename, control);
	return (parameter_exp(token, control, exp, res));
}

/*
** note:	field splitting does not occur inside a quoted section.
** note:	if the is_filename boolean is raised, splitting field will throw an
**			error of type: <<bash: $hey: ambiguous redirect>>
**
** note:	start is the first matched '$' which is neither escaped or between
**			simple quotes.
** note:	end is the index of the last character that needs to be replaced.
**
** RETURN:	0, OK
**			1, ambiguous redirect
**			2, fatal error.
*/

int		parameter_exp(t_list *token, t_control *ctrl, t_expansion exp, int res)
{
	char *insert;
	char *str;

	while ((exp.start = param_exp_find_start(token, exp.start, &exp.quoted)) \
			!= -1)
	{
		str = ((t_token *)token->content)->str;
		if ((exp.end = param_exp_find_end(token, exp.start)) == exp.start)
		{
			exp.start++;
			continue;
		}
		if (!(insert = param_exp_get_env(ctrl, str + exp.start + 1, \
				exp.end - exp.start)))
			return (2);
		//printf("expanded variable = [%s]\n", insert);
		ft_memmove(str + exp.start, str + exp.end + 1, \
				ft_strlen(str + exp.end));
		if ((res = parameter_expansion2(&token, &insert, &exp)))
		{
			free(insert);
			return (res);
		}
		free(insert);
	}
	return (0);
}

/*
** this function resets the fields of this structure to the right value
*/

void	reset_t_expansion(t_expansion *exp, int is_filename, \
		t_control *control)
{
	exp->start = 0;
	exp->end = 0;
	exp->quoted = 0;
	exp->is_filename = is_filename;
	exp->ifs = env_get("IFS", 3, control->env);
}

/*
** note:	this function tells us if the string should be expanded or not by
**			returning the indexof the non escaped and not simple quoted '$'
**			sign.
**
** RETURN:	index of start of substitution.
**			-1 elsewise
*/

int		param_exp_find_start(t_list *token, int start, char *quot)
{
	int		esc_next;
	char	*str;

	str = ((t_token*)token->content)->str;
	*quot = 0;
	esc_next = 0;
	while (str[start])
	{
		if (!esc_next && !*quot && (str[start] == '\'' || str[start] == '\"'))
			*quot = str[start];
		else if (!esc_next && *quot && str[start] == *quot)
			*quot = 0;
		if (!esc_next && str[start] == '\\')
		{
			esc_next = 1;
			start++;
			continue;
		}
		if (!esc_next && *quot != '\'' && str[start] == '$')
			return (start);
		esc_next = 0;
		start++;
	}
	return (-1);
}

/*
** note:	this funciton will return the index of the end of the expansion.
**			We start at the '$' sign, and we will stop if we meet the end of
**			the variable name.
**
** note:	special case when we have "$?" in which case the question mark is
**			included in the variable name, and marks the end of it.
**
** note:	the other special characters are treated as a whitespace or EOS...
**
** note:	the end of the variable name is marked by (non included)
**			anything that is neither a digit nor a letter nor an underscore.
**
** RETURN:	the end index (could be the start)
*/

int		param_exp_find_end(t_list *token, int start)
{
	int		end;
	char	*str;

	str = ((t_token*)token->content)->str;
	end = start + 1;
	while (str[end])
	{
		if (str[start + 1] == '?')
			return (start + 1);
		if (!ft_isalnum(str[end]) && str[end] != '_')
			break ;
		end++;
	}
	return (end - 1);
}

/*
** note:	this function will return the string matching the input env
**			variable. if the env is not set, we still Return an empty string.
**
** input:	-str is the variable (starts at the index that was after the '$'
**				sign).
**			-len: the number of characters the variable contains. (not
**				necessarily len(str)).
**
** RETURN:	char *
**			NULL if failure
*/

char	*param_exp_get_env(t_control *control, char *str, int len)
{
	char *value;
	char **addr_value;

	if (!ft_strncmp(str, "?", len))
		return (ft_itoa(control->exit_status));
	addr_value = env_get_addr(str, len, control->env);
	//printf("str: [%s], len: %d\n", str,  len);
	//printf("value: %s\n", value);
	if (!addr_value)
		value = ft_strdup("");
	else
		value = ft_strdup(*addr_value);
	return (value);
}
