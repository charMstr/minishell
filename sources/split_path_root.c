#include "minishell.h"

/*
** this file is in charge of splitting a path string into pieces,
** using a non escaped '/' as a separator.
**
*/

/*
** note:	this function will create a linked list, in which each link will
**			refer to a path_part. we basicallly break down the path using the
**			'/' valid separators in the string.
**			in each created link we find:
**				- a string for the path part itself, which will need to be
**				totally unquoted for a clean comparison with folder/file names
**				- a linked list of ints, refering to the position of the valid
**				kleen star operators within the path part string (some stars
**				could just be characters and once unquoted its impossible to
**				make the difference).
**				- a char helping us breaking quoted section.
**
** RETURN:	1 OK
**			0 KO, malloc failure.
*/

t_list	*split_path_root(char *path_to_dup_and_split)
{
	t_list *path_parts;
	char *dup_path;

	path_parts = NULL;
	if (!(dup_path = ft_strdup(path_to_dup_and_split)))
		return (NULL);
	//printf("str is: %s\n", dup_path);
	collapse_fwd_slashes(dup_path, 0, -1, 0);
	//printf("str2 is: %s\n", dup_path);
	if (!split_path(dup_path, &path_parts, 0))
	{
		free(dup_path);
		ft_lstclear(&path_parts, delete_path_part_link);
		return (NULL);
	}
	free(dup_path);
	//del me
	//debug_path_parts(path_parts);
	return (path_parts);
}

/*
** note:	this function will collapse all the mutltiple consecutive forward
**			slashes into one, exception if they are escapsed.
**			only single or double quotes can be in the middle of two
**			consecutive forward slashes.
**
** input:	str, string that may contain multiple successive '/'
**			esc_next, initially set to 0.
**			i and k, set to 0.
*/

void collapse_fwd_slashes(char *str, int esc_next, int i, int k)
{
	while (str[++i])
	{
		if (str[i] == '\\' && esc_next == 0)
		{
			esc_next = 1;
			continue;
		}
		if (esc_next != 1 && str[i] == '/')
		{
			k = i;
			while (str[++k])
			{
				if (str[k] != '/' && str[k] != '"' && str[k] != '\'')
				{
					i = k - 1;
					break;
				}
				if (str[k] == '/')
					ft_strcdel(str, k--);
			}
		}
		esc_next = 0;
	}
}

/*
** note:	this function will simply split the path where the '/' are.
**			it creats on the go some links and stores in them the string bit.
**
** RETURN:	1 OK
**			0 KO
*/

int	split_path(char *str, t_list **paths, int start)
{
	int		end;
	char	*path_part;
	char	quoted;
	char	start_quoted_at_next_path_part;

	quoted = 0;
	while (str[start])
	{
		start_quoted_at_next_path_part = quoted;
		end = find_path_end(str, start, &quoted);
		if (!(path_part = ft_substr(str, start, end - start)))
			return (0);
		//printf("\nend char: [%c]\n", str[end]);
	//	printf("full_path was:	[%s]\n", str);
		//printf("path_part = [%s]\n", path_part);
		if (!add_path_part(path_part, paths, start_quoted_at_next_path_part))
			return (0);
		if (end == (int)ft_strlen(str))
			return (1);
		start = end + 1;
	}
	if (!(path_part = ft_strdup("")))
		return (0);
	return (add_path_part(path_part, paths, start_quoted_at_next_path_part));
}

/*
** note:	this function finds the end of the current path_part. it gives
**			the index of the last character before an unescaped '/' or the
**			last index of the string before the '\0'.
**
** input:	str, the current string
**			i, the current index, start of the word.
**			quoted, lets us know if (we are or not in between brackets so that
**			even if the portions of the same string are split we know which
**			kleen star operators will be valid or not.
**
** RETURN:	int, index of the last chart part of the current path part.
*/

int	find_path_end(char *str, int i, char *quoted)
{
	int esc_next;

	esc_next = 0;
	while (str[i])
	{
		if (!esc_next & (str[i] == '"' || str[i] == '\''))
			path_set_quoted(str[i], quoted);
		if (!esc_next && str[i] == '\\')
		{
			esc_next = 1;
			i++;
			continue;
		}
		if (!esc_next && str[i] == '/')
			return (i);
		esc_next = 0;
		i++;
	}
	return (i);
}

/*
** note:	this function will activate or deactivate the fied of the path_part
**			structure called quoted.
**			*quoted can either be a single or double quote, or zero.
*/

void path_set_quoted(char c, char *quoted)
{
	if (!*quoted)
	{
		*quoted = c;
		return;
	}
	if (c == quoted[0])
		quoted[0] = 0;
}
