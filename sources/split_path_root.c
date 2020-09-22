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

int	split_path_root(char *path_to_split) //rajouter path_parts ici en arguments.
{
	t_list *path_parts;

	path_parts = NULL;

	if (!split_path(path_to_split, &path_parts))
	{
		ft_lstclear(&path_parts, delete_path_part_link);
		return (0);
	}
	//loop over path and fill the ints structure. and check for result.
	return (1);
}

/*
** note:	this function will simply split the path where the '/' are.
**			it creats on the go some links adn stores in them the string bit.
**
** RETURN:	1 OK
**			0 KO
*/

int	split_path(char *str, t_list **paths)
{
	int		end;
	int 	start;
	char	*path_part;
	char	quoted;
	char	start_quoted_at_next_path_part;

	start = 0;
	quoted = 0;
	while (str[start])
	{
		start_quoted_at_next_path_part = quoted;
		end = find_path_end(str, start, &quoted);
		if (!(path_part = ft_substr(str, start, start + end)))
			return (0);
		if (!add_path_part(path_part, paths, start_quoted_at_next_path_part))
		{
			free(path_part);
			return (0);
		}
		start = end + 1;
		printf("path_part was: [%s]\n", path_part);
		printf("hey in split__path!!!\n");
	}
	return (1);
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
		{
			return (i - 1);
		}
		esc_next = 0;
		i++;
		printf("hey in find path end!!!\n");
	}
	return (i - 1);
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

/*
** note:	this function will simply creat a link and add it to the linked
**			list of path_parts. it stores the string in the path_part
**			and initialise the rest.
**
** RETURN:	1 OK
**			0 KO
*/

int	add_path_part(char *str, t_list **path_parts, char quoted)
{
	t_path_part *new;

	if (!(new = init_path_part_link(str, quoted)))
		return (0);
	if (!unquote_path_part(new, new->path_part))
	{
		delete_path_part_link(new);
		return (0);
	}
	ft_lstadd_back(path_parts, (void *)new);
	return (1);
}

/*
** note:	this function is in charge of toggling the quoted flag.
**			if we notice that we matche a quote character that was activated,
**			we can unset the flag.
**			also each time we come accross a quote that is the begining or the
**			end of the quoted section, we eat the char and actualise the index.
*/

void path_unquoting_assist(char c, char *quoted, char *str, int *index)
{
	if (!*quoted)
	{
		*quoted = c;
		ft_strcdel(str, *index);
		(*index)--;
		//eat the char.
		return ;
	}
	else if (c == quoted[0])
	{
		//eat the char.
		ft_strcdel(str, *index);
		(*index)--;
		quoted[0] = 0;
	}
}

/*	note:	this function is called when we met an escape character. depending
**			if we are in a quoted section or not, the behavior is slighly
**			different. inside quotes, we only eat the current char if the
**			next character is also a '\\' character, otherwise it is considered
**			a regular character.
**			outsise quotes, we eat the current character no matter what.
*/

void	path_unquoting_special_escape_char(char *str, int *i, char quoted)
{
	if (quoted)
	{
		if (str[*i + 1] && str[*i + 1] == '\\')
		{
			ft_strcdel(str, *i);
			(*i)--;
		}
		return ;
	}
	ft_strcdel(str, *i);
	(*i)--;
}

/*
**	note:	this function will unquote the path_part string in the link we
**			just created. plus it will create a link list of ints,
**			corresponding to the indexes of the kleen start operators that
**			were unquoted (valid) in this path_part.
**
**	RETURN:	1 OK
**			0 KO
*/

int	unquote_path_part(t_path_part *new, char *str)
{
	int i;
	int esc_next;

	i = -1;
	esc_next = 0;
	while (str[++i])
	{
		if (!esc_next && str[i] == '\\')
		{
			esc_next = 1;
			path_unquoting_special_escape_char(str, &i, new->quoted);
			continue;
		}
		if (str[i] == '*' && !esc_next && !new->quoted)
		{
			if (!add_index_valid_kleen_star_to_lst(new, i))
				return (0);
		}
		else if (!esc_next && (str[i] == '\'' || str[i] == '"'))
			path_unquoting_assist(str[i], &new->quoted, str, &i);
		esc_next = 0;
		printf("hey in unquote_path_part!!!\n");
	}
	return (1);
}

/*
** note:	this function will add the index of a valid kleen star to a linked
**			list specialy dedicated to the task in the t_path_part struct,
**			calle star_index.
**
** RETURN:	1, OK
**			0 KO
*/

int	add_index_valid_kleen_star_to_lst(t_path_part *new, int index)
{
	int	*i;

	if (!(i = malloc(sizeof(int))))
		return (0);
	*i = index;
	ft_lstadd_back(&new->star_index, (void *)i);
	return (1);
}

/*
** note:	this function will initialise a path_part link
**
** RETURN:	pointer, OK
**			NULL KO
*/

t_path_part *init_path_part_link(char *str, char quoted)
{
	t_path_part *new;

	if (!str)
		return (NULL);
	if (!(new = (t_path_part *)malloc(sizeof(t_path_part))))
		return (NULL);
	new->path_part = str;
	new->star_index = NULL;
	new->quoted = quoted;
	return (new);
}

/*
** note:	this function will delete the t_path_part structure.
*/

void	delete_path_part_link(void *content)
{
	t_path_part *elem;
	elem = (t_path_part*)content;
	free(elem->path_part);
	ft_lstclear(&(elem->star_index), free);
	ft_free((void *)&elem);
}
