#include "minishell.h"

/*
** this file will make sure there is no multiline pending regargding the
** apostrophes symbols (',",`).
*/

/*
** note:	this function will parse the full raw string taken from the user
**			intput and check that there is no unmatching apostrophes.
** RETURN:	1 OK
**			0 mismatch (multiline case...)
*/

int	pars_no_multiline(char *line)
{
	int i;
	int match_index;
	int escape;

	i = 0;
	escape = 0;
	while (line[i])
	{
		if (escape == 1 && line[i] == '\\')
			escape = 0;
		else if (line[i] == '\\')
			escape = 1;
		else if (!escape && \
				(line [i] == '\'' || line[i] == '\"' || line[i] == '`'))
		{
			if ((match_index = ft_strichr_esc(line + i + 1, line[i])) == -1)
				return (0);
			else
				i += match_index + 1;
		}
		else
			escape = 0;
		i++;
	}
	return (1);
}

/*
** note:	this function will find the index of the next non escaped char c.
**			it is basically a copy of the strichr function, plus the feature of
**			neglecting a char if its predecessor ia a '\'.
** RETURN:	-1 if char not found.
**			the index of the next char c in the sting.
*/

int	ft_strichr_esc(const char *str, char c)
{
	int i;
	int escaped;

	i = 0;
	escaped = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (escaped == 1 && str[i] == '\\')
			escaped = 0;
		else if (str[i] == '\\')
			escaped = 1;
		else if (!escaped && str[i] == c)
			return (i);
		else
			escaped = 0;
		i++;
	}
	return (-1);
}
