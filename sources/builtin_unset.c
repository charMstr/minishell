#include "minishell.h"

/*
** this file is a subset of the builtin_root.c file.
** It takes care of the unset builtin.
*/

/*
** note:	the unset can take more than one argument, therefore we will loop
**			over each of them
**
** note:	we assume that we do call the function with the argv[0] as being
**			the builtin name
** RETURN:	0
*/

int	unset_builtin(t_list **env_head, char **argv)
{
	int i;
	int res;

	i = 1;
	res = 0;
	while (argv[i])
	{
		printf("truc a enlever:[%s]\n", argv[i]);
		res = unset_in_env_list(env_head, argv[i]);
		i++;
	}
	return (res);
}

/*
** note:	this function will try to find a matching label in the linked list
**			and remove it.
** note:	if the link is found, note: that we use *ptr (and not ptr) to
**			really afect the list (*ptr = (*ptr)->next). And we free the link
**			and set it to NULL. Terefore if it is the last link, the head of
**			the list is set to NULL.
**
** RETURN:	0 the unset was successful
**			0 elsewise.
*/

int	unset_in_env_list(t_list **env_head, char *str)
{
	t_list **ptr;
	t_list *extra;

	ptr = env_head;
	while (*ptr)
	{
		if (!ft_strncmp(str, ((t_env*)((*ptr)->content))->label, \
					ft_strlen(str) + 1))
		{
			extra = *ptr;
			*ptr = (*ptr)->next;
			env_del_struct(extra->content);
			free(extra);
			return (0);
		}
		ptr = &(*ptr)->next;
	}
	return (0);
}
