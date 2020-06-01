#include "minishell.h"

/*
** this file is supporting the export builtin.
*/

/*
** note:	The export builtin will edit the t_list containing the t_env
**			structure. If the list is empty, a new head is created.
** note:	The export can have more than one arg to add at a time. It is
**			assumed that the very first arg is the builtin name (argv[0]) so
**			we start at argv[1];
**
** RETURN:	1 if OK
**			0 if malloc failed.
*/

//note: control quit should be updated accordingly... same goes for exit status

int export_builtin(t_list **head, char **argv)
{
	int i;
	char **str_addr;
	char *sep2;

	i = 1;
	while (argv[i])
	{
		if (!(sep2 = export_builtin_check_label(argv[i])))
		{
			i++;
			continue;
		}
		if ((str_addr = env_get_addr(argv[i], ft_strlen(argv[i]), *head)))
		{
			ft_free((void **)str_addr);
			if (!(*str_addr = ft_strdup(sep2)))
				return (0);
		}
		else if (!export_builtin_new_env(argv[i], sep2, head))
			return (0);
		i++;
	}
	return (1);
}

/*
** note:	This function will check the validity of the str we receive.
**			It will display an error message if have a string starting by
**			either a '=' or a '\'. note that the error is note fatal, and the
**			subsequent arguments to the same export are still processed.
**
** note:	If the string does not contain a '=' at all
**			nothing is done at all and we Return a non fatal NULL
**
** note:	if the string is valid, we perform a str_sep and return the
**			pointer on the second half.
**
** RETURN:	char * that is the futur value in the t_env struct
**			NULL: no '=' found, or wrong first char, so process with next argv.
*/

char *export_builtin_check_label(char *str)
{
	int i;

	if (str[0] == '=' || str[0] == '\\')
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (NULL);
	}
	if ((i = ft_strichr(str, '=')) == -1)
		return (NULL);
	str[i] = '\0';
	return (str + i + 1);
}

/*
** note:	this function is called when the link containing the matchin label
**			wasn't found in the env variable list. We then creat a new link
**			and append it at the end of the link list.
** input:	- str: the label (first part of argv[1] when sep with a '\0')
**			- str2: the value (second part of argv[1])
*/

int export_builtin_new_env(char *str, char *str2, t_list **head)
{
	t_env *env;
	t_list *new_link;

	if (!(env = ft_memalloc(sizeof(t_env))))
		return (0);
	if (!(env->label = ft_strdup(str)))
	{
		free(env);
		return (0);
	}
	if (!(env->value = ft_strdup(str2)))
	{
		free(env->label);
		free(env);
		return (0);
	}
	if (!(new_link = ft_lstnew(env)))
	{
		env_del_struct(env);
		return (0);
	}
	ft_lstadd_back(head, new_link);
	return (1);
}
