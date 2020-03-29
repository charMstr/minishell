#include "minishell.h"

/*
** this file is in charge -- see function bellow.
*/

/*
** note:	this function will split the line entered by the user in different
**			commands regarding to the character ";" or "|".
**
** RETURN:	char **
**			NULL if failure from malloc.
*/

char ** pars_split_commands(char *line, char c)
{
	int i;
	char **tab;
	int size;
	int j;

	i = 0;
	j = 0;
	size = pars_count_cmds(line, c);
	if (!(tab = (char **)malloc(sizeof(*tab) * (size + 1))))
		return (NULL);
	tab[size] = NULL;
	while (i < size)
	{
		if (!(tab[i] = pars_get_next_cmd_word(line, &j, c)))
		{
			ft_free_2d(tab);
			return (NULL);
		}
		i++;
	}
	return (tab);
}

/*
** note:	this function will predict the number of commands or subsets of
**			commands(in the case of a pipelined comand) so that we can
**			allocate the correct number of line in our multidimensional array.
** note:	the char c cannot be any of the apostrophes characters ('"`).
** RETURN:	char **
**			NULL if malloc failed
*/

int	pars_count_cmds(char *line, char c)
{
	int i;
	int count;
	int match_index;

	i = 0;
	count = 1;
	while (line[i])
	{
		if (line[i] == c)
			count++;
		else if (line [i] == '\'' || line[i] == '\"' || line[i] == '`')
		{
			if ((match_index = ft_strichr_esc(line + i + 1, line[i])) == -1)
				return (0);
			else
				i += match_index + 1;
		}
		i++;
	}
	return (count);
}

/*
** note:	this function will jump for the sections that are protected from
**			being split since they are a quoted section (between apostrophes).
** RETURN:	the number of characters to jump (add to the incrementing var).
*/

int pars_jump_quoted_section(char *line)
{
	int i;
	char c;

	i = 0;
	if (*line != '\''  && *line != '\"' && *line != '`')
		return (0);
	else
		c = *line;
	if (line[0])
		i++;
	while (line[i] && (line[i] != c))
		i++;
	return (i);
}

/*
** note:	This function will get the next "word" for us within the line.
**			Words are separated by the c character, and the function
**			pars_jump_quoted_section() is used to avoid spliting thoses by
**			making jumps.
** note:	the index pointer is updated so that we can keep track of where we
**			are on the next run regarding to the very beginning of line.
** RETURN:	char *
** 			NULL fi malloc failed.
*/

char	*pars_get_next_cmd_word(char *line, int *index, char c)
{
	char *str;;
	int start;

	start = *index;
	while (line[*index])
	{
		if (line[*index] == c)
			break;
		*index  += pars_jump_quoted_section(line + *index);
		(*index)++;
	}
	if (!(str = ft_substr(line, start, *index - start)))
		return (NULL);
	if (line[*index])
		(*index)++;
	return (str);
}
