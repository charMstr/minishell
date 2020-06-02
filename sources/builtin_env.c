#include "minishell.h"

/*
** this file will be in charge of anything in relation to environment variables
*/

/*
** note:	this function will represent the env buit-in facility
**			it just displays the env list, and set the exit status to 0
**
** RETURN:	always 1. and therefore the exit_status is always 0
*/

int env_builtin(t_list *env, t_control *control)
{
	while (env)
	{
		ft_putstr_fd(((t_env *)env->content)->label, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(((t_env *)env->content)->value, 1);
		env = env->next;
	}
	control->exit_status = 0;
	return (1);
}

/*
** note:	this function will build the env linked list. using as input the
**			exter char **environ
**
** RETURN:	t_list *
**			NULL malloc failed
*/

t_list	*env_build_linked_list(char **env)
{
	t_list	*lst_head;
	t_list	*lst_link;
	t_env	*env_struct;
	int		i;

	i = 0;
	lst_head = NULL;
	while (env[i])
	{
		if (!(env_struct = env_build(env[i])))
		{
			ft_lstclear(&lst_head, env_del_struct);
			return (NULL);
		}
		if (!(lst_link = ft_lstnew(env_struct)))
		{
			env_del_struct(env_struct);
			ft_lstclear(&lst_head, env_del_struct);
			return (NULL);
		}
		ft_lstadd_back(&lst_head, lst_link);
		i++;
	}
	return (lst_head);
}
/*
	//debug_env_list(lst_head);
	char *argv[] = {"MAIL", "PS1", "PS2", "CLICOLOR", NULL };
	printf("--------------------------avant\n");
	env_builtin(lst_head);
	printf("--------------------------avant\n");
	printf("==========================ON ENLEVE:\n");
	unset_builtin(&lst_head, argv);
	env_builtin(lst_head);
	printf("==========================ON ENLEVE\n");
	printf("-------------------------APRES\n");
	export_builtin(&lst_head, argv);
	env_builtin(lst_head);
	printf("-------------------------APRES\n");
	return (1);
}
*/

/*
**	note:	this function will be called when its necessary to free the list of
**			t_env structs.
*/

void	env_del_struct(void *env)
{
	free(((t_env *)env)->label);
	free(((t_env *)env)->value);
	free((t_env *)env);
}

/*
** note:	This function will get the string either imported from the env
**			variable list that we are converting at the start. Or from the
**			export utility. in the second case, the validity of the string has
**			already been checked (equal sign present, str not starting by a '='
**			or a '\')
**			It split str at the first '=' sign found into two elements of a
**			struct: label and value.
**
** RETURN:	t_env *
**			NULL if some malloc failed.
*/

t_env	*env_build(char *str)
{
	int		i;
	t_env	*new;

	if ((i = ft_strichr(str, '=')) == -1)
		return (NULL);
	if (!(new = env_init_struct()))
		return (NULL);
	if (!(new->label = ft_substr(str, 0, i++)) ||
		!(new->value = ft_substr(str + i, 0, ft_strlen(str + i))))
	{
		env_del_struct(new);
		return (NULL);
	}
	return (new);
}

/*
** note:	this function will init the env struc and set its subfields to NULL
**
** RETURN:	null if failure in malloc
**			t_env *
*/

t_env	*env_init_struct(void)
{
	t_env *new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	new->label = NULL;
	new->value = NULL;
	return (new);
}

/*
** note:	this function will return the value of the string matching the env
**			variable given as input.
**
** note:	as input we give len, so str could be a substring of a char *.
**
** RETURN:	char * (not malloced! just a copy)
**			NULL if env does not exist
*/

char	*env_get(char *str, size_t len, t_list *env)
{
	while (env)
	{
		if (((t_env*)env->content)->label)
		{
			if (ft_strlen(((t_env*)env->content)->label) == len \
					&& !ft_strncmp(str, ((t_env*)env->content)->label, len))
				return (((t_env*)env->content)->value);
		}
		env = env->next;
	}
	return (NULL);
}

/*
** note:	this function will return the address of the value of the label
**			string matching the env variable given as input.
**
** note:	as input we give len, so str could be a substring of a char *.
**
** RETURN:	char **.
**			NULL if env does not exist
*/

char	**env_get_addr(char *str, size_t len, t_list *env)
{
	while (env)
	{
		if (((t_env *)env->content)->label)
		{
			if (ft_strlen(((t_env *)env->content)->label) == len \
					&& !ft_strncmp(str, ((t_env *)env->content)->label, len))
				return (&((t_env *)env->content)->value);
		}
		env = env->next;
	}
	return (NULL);
}
