#include "minishell.h"

/*
** note:	this function tells us if the string should be expanded or not by
**			returning the indexof the non escaped and not simple quoted '$'
**			sign.
**
** RETURN:	index of start of substitution.
**			-1 elsewise
*/

int	param_exp_find_start(t_list **token, int start, char *quot)
{
	int esc_next;
	char *str;

	str = ((t_token*)(*token)->content)->str;
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
** note:	the end of the variable name is marked by(non included) whitespace,
**			or '*', or '\', or quote, or the end of the string.
**
** RETURN:	the end index (could be the start)
*/

int		param_exp_find_end(t_list **token, int start)
{
	int end;
	char *str;

	str = ((t_token*)(*token)->content)->str;
	end = start + 1;
	while (str[end])
	{
		if (str[start + 1] == '?')
			return (start + 1);
		if (str[end] == '*' || str[end] == '\\' || str[end] == '\'' \
				|| str[end] == '\"' || str[end] == '$' || str[end] == ' ')
			break;
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

char *param_exp_get_env(t_control *control, char *str, int len)
{
	char *value;

	if (!ft_strncmp(str, "?", len))
		return (ft_itoa(control->exit_status));
	value = env_get(str, len, control->env);
	//printf("str: [%s], len: %d\n", str,  len);
	//printf("value: %s\n", value);
	if (!value)
		value = ft_strdup("");
	else
		value = ft_strdup(value);
	return (value);
}

/*
** this function resets the fields of this structure to the right value
*/
void	reset_t_expansion(t_expansion *exp, int field_splitting)
{
	exp->start = 0;
	exp->end = 0;
	exp->quoted = 0;
	exp->field_splitting = field_splitting;
	exp->ifs = NULL;
}

/*
** note:	This function will operate the parameter expansion on a given token
**			The token->str, might end up creating multiple tokens in the case
**			some field splitting is done. In that case, a new token is created
**			for each field separation, and inserted in place into the linked
**			list.
**
** note:	start is the first matched '$' which is neither escaped or between
**			simple quotes.
** note:	end is the index of the last character that needs to be replaced.
**
** RETURN:	1 OK
**			0 KO
*/

int	parameter_expansion(t_list **token, t_control *control, int field_split)
{
	t_expansion exp;
	char *insert;
	char *str;

	reset_t_expansion(&exp, field_split);
	while ((exp.start = param_exp_find_start(token, exp.start, &exp.quoted)) \
			!= -1)
	{
		str = ((t_token *)(*token)->content)->str;
		if ((exp.end = param_exp_find_end(token, exp.start)) == exp.start)
			return (1);
		insert = param_exp_get_env(control, str + exp.start + 1, \
				exp.end - exp.start);
		//printf("insert: vairable = [%s]\n", insert);
		ft_memmove(str + exp.start, str + exp.end + 1, \
				ft_strlen(str + exp.end));
		if (!param_exp2(token, control, insert, &exp))
		{
			free(insert);
			return (0);
		}
		free(insert);
	}
	return (1);
}
