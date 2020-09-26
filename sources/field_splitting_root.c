/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting_root.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:46:26 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 20:09:01 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file is in charge of doing the field splitting on a given tooken and
** its string. therefor creating multiple tokens.
*/

/*
** note:	this function is the root function for the field splitting.
**			It will do a splitwhitespaces onto the value fetched into the
**			env list. and insert it in place into the original string which is
**			split into two bits: str1 and str2.
**			separating it into at least two or more strings.
**
** inputs: 	token, containing the str to be updated w/ the splitted string.
**				it is a tripple ref so that we can advance the
**			var, the value of the env variable string that will be splitted.
**			exp, the struct containing all the relevant data for inserting var.
**
** RETURN:	1,  OK
**			0,	KO, malloc failure
*/

int	field_splitting_root(t_list **token, char *var, t_expansion *exp)
{
	char *str1;
	char *str2;

	str1 = ((t_token*)(*token)->content)->str;
	if (!(str2 = ft_substr(str1, exp->start, ft_strlen(str1) + exp->start)))
		return (0);
	str1[exp->start] = '\0';
	if (!field_splitting_root_assist(token, exp, var, str2))
	{
		free(str2);
		return (0);
	}
	free(str2);
	return (1);
}

/*
** note:	at this stage, we try to field split creating an array.
**			The current token's string is str1, and the second part str2
**			is given as a parameter. In between str1 and str2 is going to be
**			appended the result of the field splitting upon the var string.
**
**
** input:	-var: the string to be splitted.
**			-token: in which is str1, to which we will append var's first field
**			-exp: the structure containg start and field_splitting
**			-str2: will be appended to the last token.(could be the first one
**			if no splitting occurs.
**
** RETURN:	1 OK
**			0 KO, fatal error.
*/

int	field_splitting_root_assist(t_list **token, t_expansion *exp, char *var,\
		char *str2)
{
	char	**array;

	if (!exp->ifs)
	{
		if (!(array = ft_split_whitespaces(var, " \n\t")))
			return (0);
	}
	else if (!(array = ft_split_whitespaces(var, exp->ifs)))
		return (0);
	((t_token *)(*token)->content)->protect_e = exp->start + \
				ft_strlen(array[0]);
	if (!field_splitting(token, exp, array, str2))
	{
		ft_array_free(array, ft_array_len(array));
		return (0);
	}
	ft_array_free(array, ft_array_len(array));
	return (1);
}

/*
** note:	at this stage, we already commited to field splitting, therefor the
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

int	field_splitting(t_list **tok, t_expansion *exp, char **array, char *str2)
{
	char	**str;
	int		i;

	i = 1;
	str = &((t_token*)(*tok)->content)->str;
	if (array[0] && !(*str = ft_strjoin_free(*str, array[0], 1)))
		return (0);
	while (array[i])
	{
		tok = &(*tok)->next;
		if (!(field_splitting_assist(tok, array[i])))
			return (0);
		i++;
	}
	str = &((t_token*)(*tok)->content)->str;
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
	t_list	*new_link;
	t_token	*new_token;

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
