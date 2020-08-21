/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:30:40 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 11:30:41 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** note:	this file will take care of inserting in the actual string, the
**			expansion of the $VAR. field splitting can occur creating multiple
**			tokens in place.
*/

/*
** note:	This func will  call a subf to assess if field splitting should
**			occur.
**			An error can be detected if field splitting is due and we are in
**			the case of a filename.
**			The start of the protection against unquoting is set (last stage
**			of the word expansion). and then we either split (creat/insert new
**			tokens) or just insert the new string.
**
** inputs:	token containing the str
**			var: the string to insert
**			x: 	the struct containing all the fields necessary for insertion
**
** RETURN:	0, OK
**			1, KO, ambiguous redirect due to field split + filename
**			2, KO, fatal error.
*/

int	parameter_expansion2(t_list **token, char **var, t_expansion *exp)
{
	int field_split;

	((t_token *)(*token)->content)->unquote_protected = 1;
	((t_token *)(*token)->content)->protect_s = exp->start;
	field_split = need_to_field_split1(var, exp);
	if (field_split == 2 || (field_split == 1 && exp->is_filename))
		return (field_split);
	if (!field_split)
	{
		if (!param_exp_no_fsplit(*token, *var, exp))
			return (2);
	}
	else
	{
		if (!field_splitting_root(token, *var, exp))
			return (2);
	}
	return (0);
}

/*
** note:	this function will predict if there is some field splitting to be
**			done, if not, we simply apply the quote_removal functions.
** note:	the IFS was collected from the env variables.
**
** RETURN:	1 need to field split
**			0 no need to.
**			2, fatal error
*/

int	need_to_field_split1(char **str, t_expansion *exp)
{
	char *tmp;

	tmp = *str;
	if (exp->quoted || (exp->ifs && !ft_strlen(exp->ifs)))
		return (0);
	if (!exp->ifs)
	{
		if (!(*str = ft_strtrim(*str, " \t\n")))
		{
			free(tmp);
			return (2);
		}
		free(tmp);
		if (-1 != ft_stristr(*str, " \t\n"))
			return (1);
		return (0);
	}
	else
	{
		return (need_to_field_split2(str, exp));
	}
}

/*
** note:	this function assist the function need_to_field_split1
**
** RETURN:	1 need to field split
**			0 no need to.
**			2, fatal error
*/

int	need_to_field_split2(char **str, t_expansion *exp)
{
	char *tmp;

	tmp = *str;
	if (!(*str = ft_strtrim(*str, exp->ifs)))
	{
		free(tmp);
		return (2);
	}
	free(tmp);
	if (-1 != ft_stristr(*str, exp->ifs))
		return (1);
	return (0);
}

/*
** note:	this function is called when field splitting was assessed but no
**			splitting occured, or we were simply in a quoted section.
**			the start index is updated. the end of the protected against
**			unquoting section is set to start + len(var).
**
** RETURN:	1 OK
**			0 KO
*/

int	param_exp_no_fsplit(t_list *token, char *var, t_expansion *exp)
{
	char **ptr_str;

	ptr_str = &((t_token*)token->content)->str;
	((t_token *)token->content)->protect_e = ft_strlen(var) + exp->start;
	if (!ft_strstradd(ptr_str, exp->start, var))
		return (0);
	exp->start += ft_strlen(var);
	return (1);
}
