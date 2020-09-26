#include "minishell.h"

/*
** this file is in charge of finding the matches between the path containing
** a valid kleen start operator and the real folder/file names.
*/

/*
** note:	this function is the root for matching a pathname with the
**			successive directory streams and file. we will decide if we are in
**			the case of an absolute or relative path. but both function then
**			will use the same recursive func. pahtname_matching()
**
** note:	All the parts of the pathname are contained in the linked list
**			path_parts, and we know there is at least one character in it.
**			Otherwise we would not execute this code thanks to
**			pathname_is_expandabble().
**
** note:	when all the path parts of the linked list are validated,
**			we reach NULL and the path to a temporary linked list.
**
** note:	returning 0 means we had either 0, 1 or several matches, but
**			everything went well. then it will be necessary to look at the
**			matched_paths pointer.
**
** RETURN:	0, OK
**			1, ambiguous redirect. (is_filename == 1 && more than one match)
**			2, fatal error
*/

int	pathname_matching_root(t_path_exp *tool, t_list *path_parts)
{
	char *first_path_part;

	first_path_part = ((t_path_part *)(path_parts->content))->path_part;
	if (!ft_strlen(first_path_part))
		return (pathname_matching(tool, path_parts->next, "", "/"));
	else if (!ft_strcmp(first_path_part, "."))
		return (pathname_matching(tool, path_parts->next, ".", "./"));
	else if (!ft_strcmp(first_path_part, ".."))
		return (pathname_matching(tool, path_parts->next, "..", "../"));
	else
		return (pathname_matching_relative(tool, path_parts));
}

/*
** note:	this function will be called when we have a relative path, ie the
**			very first link of the path_parts contains a path_part that is a
**			non empty string. (something was befor the firs '/' separator).
**
** RETURN:	0, OK
**			1, ambiguous redirect.
**			2, fatal error
*/

int pathname_matching_relative(t_path_exp *tool, t_list *path_parts)
{
	DIR		*dir_p;
	struct	dirent *entry;
	int		res;
	char	*path_start;

	if (!(dir_p = opendir("./")))
		return (0);
	while ((entry = readdir(dir_p)) != NULL)
	{
		if (match_path_part_root(path_parts, entry->d_name))
		{
			if (!(path_start = ft_strdup(entry->d_name)))
				return (2);
			res = pathname_matching(tool, path_parts->next, path_start, \
					path_start);
			free(path_start);
			if (res)
				return (res);
		}
	}
	closedir(dir_p);
	return (0);
}

/*
** note:	This is the recusive function, that will try to match all the
**			path parts other than the very first one.
**
** 			At each match we concatenate the path_start, a '/' and the matching
**			filename or directory. note that the very last link could contain
**			an empty string, it means just join the '/' at the end.
**
** inputs:	path_start, the current malloced string, containing the begining of
**				the	path so far.
**			tool, containing all the necessary informations.
**			path_parts, linked list to the path_parts. reaching NULL means we
**				have a complete match with the path.
**			to_open, the directory stream to be opened.
**
** RETURN:	0, OK.
**			1, ambiguous redirect.
**			2, fatal error.
*/

int pathname_matching(t_path_exp *tool, t_list *path_parts, char *path_start, \
		char *open_me)
{
	int		res;
	char	*path_fuller;
	DIR		*dir_p;

	if (!path_parts)
		return (pathname_matched_add_to_list(tool, path_start));
	if (!ft_strlen(((t_path_part *)path_parts->content)->path_part))
	{
		if (!(dir_p = opendir(open_me)))
			return (0);
		if (!(path_fuller = ft_strjoin(path_start, "/")))
			return (2);
		res = pathname_matched_add_to_list(tool, path_fuller);
		free(path_fuller);
		closedir(dir_p);
		return (res);
	}
	return (pathname_matching_assist(tool, path_parts, path_start, open_me));
}

/*
** note:	this function assist the recurcive function.
*/

int pathname_matching_assist(t_path_exp *tool, t_list *path_parts, \
		char *path_start, char *open_me)
{
	DIR		*dir_p;
	struct	dirent *entry;
	int		res;
	char	*path_fuller;

	if (!(dir_p = opendir(open_me)))
		return (0);
	while ((entry = readdir(dir_p)) != NULL)
	{
		if (match_path_part_root(path_parts, entry->d_name))
		{
			if (!(path_fuller = path_join(path_start, entry->d_name)))
				pathname_matching_closedir_return(dir_p, 2);
			res = pathname_matching(tool, path_parts->next, path_fuller, \
					path_fuller);
			free(path_fuller);
			if (res)
				pathname_matching_closedir_return(dir_p, res);
		}
	}
	closedir(dir_p);
	return (0);
}

/*
** note:	this function will concatenate the already validated path_start,
**			with a '/' character and with an entry from the directory_stream
**			that just matched another path part.
**
** RETURN:	char *, OK
**			NULL, KO
*/

char	*path_join(char *str, char *str2)
{
	char *intermediate;
	char *final;

	if (!str || !str2)
		return (NULL);
	if (!(intermediate = ft_strjoin(str, "/")))
		return (NULL);
	if (!(final = ft_strjoin_free(intermediate, str2, 1)))
		return (NULL);
	return (final);
}
