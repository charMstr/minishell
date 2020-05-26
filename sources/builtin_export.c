#include "minishell.h"

/*
** this file is is a subset of the builtin_root.c file.
** It is supporting the export builtin.
*/

/*
** note:	the export builtin will edit the t_list containing the t_env
**			structure.
** note:	if the list is empty, a new head is created.
** note:	the export can have more than one arg to add at a time.
** note:	it is assumed that the very first arg is the builtin name (argv[0])
**			so we start at argv[1];
**
** RETURN:	0 if ok
**			1 if malloc failed.
*/

int export_builtin(t_list **head, char **argv)
{
	int i;
	t_env *env;
	t_list *new_link;

	i = 1;
	while (argv[i])
	{
		if (!(env = env_build(argv[i])))
			return (1);
		if (!(new_link = ft_lstnew(env)))
			return (1);
		ft_lstadd_back(head, new_link);
		i++;
	}
	return (0);
}
