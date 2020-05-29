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

int	param_exp_field_split2(t_list **token, t_expansion *exp, char **array, \
		char *str2)
{
	//HERE, and field_splitting
	(void)token;
	(void)exp;
	(void)array;
	(void)str2;
	return (1);
}

/*
** note:	at this stage, we try to field split creating array.
**			The current token's string is str1, and the second part str2
**			is given as a parameter. In between str1 and str2 is going to be
**			appended the result of the field splitting upon var string.
** note:	if the array is only containing one char * (no splitting occured),
**			the contatenation in the current token is done like so:
**			str1 + var + str2, and start index is updated like if no field
**			splitting ever occured. if splitting ->subfunction.
**
** input:	-var: the string to be splitted.
**			-token: in which is str1, to which we will append var's first field
**			-exp: the structure containg start and field_splitting
**			-str2: will be appended to the last token.(could be the first one
**			if no splitting occurs.
**
** RETURN:	1 OK
**			0 KO
*/

int	param_exp_field_split(t_list **token, t_expansion *exp, char *var, \
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
	if (ft_array_len(array) == 1)
	{
		ft_array_free(array, ft_array_len(array));
		return (param_exp_no_fsplit(&((t_token*)(*token)->content)->str, var,
					str2, exp));
	}
	if (!param_exp_field_split2(token, exp, array, str2))
	{
		ft_array_free(array, ft_array_len(array));
		return (0);
	}
	ft_array_free(array, ft_array_len(array));
	return (1);
}

/*
** note:	this function is called when field splitting was tried but no
**			splitting occured. then var contains exactly the copy  as the
**			array[0], so the array is thrown away before entering the func.
**			the start index is updated as if we never entered the field
**			splitting function.
**
** RETURN:	1 OK
**			0 KO
*/

int	param_exp_no_fsplit(char **str, char *var, char *str2, t_expansion *exp)
{
	if (!(*str = ft_strjoin_free(*str, var, 1)))
		return (0);
	if (!(*str = ft_strjoin_free(*str, str2, 1)))
		return (0);
	exp->start += ft_strlen(var);
	return (1);
}

/*
** note:	this function will decide if we operate the field splitting algo
**			or not onto the parameter expansion.
**			If not we simply insert ther var string into the current token's
**			str. If yes we will have to eventually creat new tokens
**
** RETURN:	1 OK
**			0 KO
*/

int	param_exp2(t_list **token, t_control *control, char *var, t_expansion *x)
{
	char *str2;
	char **str;

	x->ifs = env_get("IFS", 3, control->env);
	str = &((t_token *)(*token)->content)->str;
	if (x->quoted || !x->field_splitting || (x->ifs && !ft_strlen(x->ifs)))
	{
		if (!ft_strstradd(str, x->start, var))
			return (0);
		x->start += ft_strlen(var);
		return (1);
	}
	else
	{
		//printf("we are going to field split\n");
		//printf("entering with *str = [%s]\n", *str);
		if (!(str2 = ft_substr(*str, x->start, ft_strlen(*str) + x->start)))
			return (0);
		(*str)[x->start] = '\0';
	//	printf("str1 = [%s]\n", *str);
	//	printf("str2 = [%s]\n", str2);
		if (!param_exp_field_split(token, x, var, str2))
		{
			return (0);
			free(str2);
		}
		free(str2);
	}
	return (1);
}
