#include "minishell.h"

/*
** this file is supporting the export builtin.
*/

/*
** note:	The export builtin will edit the t_list containing the t_env
**			structure.
** note:	If the list is empty, a new head is created.
** note:	The export can have more than one arg to add at a time.
** note:	It is assumed that the very first arg is the builtin name (argv[0])
**			so we start at argv[1];
** note:	For every argument. if there is no
**
** RETURN:	1 if OK
**			0 if malloc failed.
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
		{
			env_del_struct(env);
			return (1);
		}
		ft_lstadd_back(head, new_link);
		i++;
	}
	return (0);
}


//note: if we dont have the equal sign, the export is not done at all!

//note:quote removal is done before anything else in bash. well it is actually
//done like any other f*** command

//note:	the char * label cannot start by the '=' or the '\' char otherwise:
//	bash: export: `\hey': not a valid identifier
//	bash: export: `=salut': not a valid identifier
// and this is after the processing of expansion and quote reomval! especially
// for the '\'...
//note: at export time. the string should go through the process:
// parameter expansion (without field spliting)
// unquoting
// need to handle the case when the input is wrong, look for error messages
// from the shell.
//need to handle the case where the env var already exists.
