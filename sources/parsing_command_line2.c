#include "minishell.h"

/*
** this file is in charge of parsing the double dimension array containing
** separated commands to be run sequentialy.
*/

/*
** note:	this function will parse each array.
** note:	special case for the string (command) of the array since it is the
**			only one that can be empty or only containing whitespaces.
** 			and it this special case, the token is `;' and not `newline'
** RETURN:	0 if everything went well
**			Or a value that matchs the exit status we are going to set while
**			aborting any execution.
*/

int	pars_separated_runs_array(char **tab)
{
	int i;
	int len;
	int res;

	i = 0;
	len = len_2d(tab);
	while (i < len)
	{
		if (i < len -1)
		{
			if ((res = pars_separated_runs_string(tab[i], 0)))
				return (res);
		}
		else
		{
			if ((res = pars_separated_runs_string(tab[i], 1)))
				return (res);
		}
		i++;
	}
	return (0);
}

/*
** note:	this function will do the parsing for each sequantial commands.
**			special case for the very last one, which is the only one that can
**			be an empty line or whitespaces only.
** RETURN:	0 if OK
**			exit_status to be displayed otherwise.
*/

int	pars_separated_runs_string(char *str, int very_last)
{
	char *trimed;

	trimed = NULL;
	if (!(trimed = ft_strtrim(str, " ")))
		return (-1);
	if (!very_last && !ft_strlen(trimed))
	{
		free(trimed);
		pars_unexpected_token(";");
		return (258);
	}
	if (trimed[ft_strlen(trimed) - 1] == '(')
	{
		free(trimed);
		if (very_last)
			pars_unexpected_token("newline");
		else
			pars_unexpected_token(";");
		return (258);
	}
	free(trimed);
	return (0);
}

void	pars_unexpected_token(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
}
