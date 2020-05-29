#include "minishell.h"

/*
** note:	this function will decide if we operate the field splitting algo
**			or not onto the parameter expansion.
**			If not we simply insert ther var string into the current token's
**			str. If yes we will have to eventually creat new tokens
**
** note:	the token->unquote_protected and its related start and end will
**			mark the begining and end of the inserted expanded variable.
** RETURN:	1 OK
**			0 KO
*/

int	param_exp2(t_list ***token, t_control *control, char *var, t_expansion *x)
{
	char *str2;
	char **str;

	str = param_exp2_assist(x, **token, control);
	if (x->quoted || !x->field_splitting || (x->ifs && !ft_strlen(x->ifs)))
	{
		((t_token *)(**token)->content)->protect_e = ft_strlen(var) + x->start;
		if (!ft_strstradd(str, x->start, var))
			return (0);
		x->start += ft_strlen(var);
		return (1);
	}
	else
	{
		//printf("we are going to attempt to field split\n");
		//printf("once the $var collapsed: str = [%s]\n", *str);
		if (!(str2 = ft_substr(*str, x->start, ft_strlen(*str) + x->start)))
			return (0);
		(*str)[x->start] = '\0';
		//printf("before param expansion: (str1) = [%s]\n", *str);
		//printf("after param expansion: (str2)  = [%s]\n", str2);
		if (!param_exp_field_split(token, x, var, str2))
		{
			free(str2);
			return (0);
		}
		free(str2);
	}
	return (1);
}

/*
** note:	assising the param_exp2 func
*/

char **param_exp2_assist(t_expansion *x, t_list *token, t_control *control)
{
	x->ifs = env_get("IFS", 3, control->env);
	((t_token *)token->content)->unquote_protected = 1;
	((t_token *)token->content)->protect_s = x->start;
	return (&((t_token *)token->content)->str);
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

int	param_exp_field_split(t_list ***token, t_expansion *exp, char *var, \
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
	((t_token *)(**token)->content)->protect_e = exp->start + \
				ft_strlen(array[0]);
	if (ft_array_len(array) == 1)
	{
		ft_array_free(array, ft_array_len(array));
		return (param_exp_no_fsplit(&((t_token*)(**token)->content)->str, var,
					str2, exp));
	}
	//printf("\nthe field splitting resulted in more that one field:");
	//debug_array(array);
	if (!field_splitting(token, exp, array, str2))
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
