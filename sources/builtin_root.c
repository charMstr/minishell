#include "minishell.h"

/*
** this file will be in charge of anything in relation to environment variables
*/

/*
** note:	this function will build the env linked list.
** RETURN:	1 ok
**			0 malloc failed
*/

extern char **environ;

int	env_build_linked_list(char **env)
{	t_list *lst_head;
	t_list *lst_link;
	t_env *env_struct;
	int i;

	i = 0;
	lst_head = NULL;
	while (env[i])
	{		if (!(env_struct = env_build(env[i])))
		{
			ft_lstclear(&lst_head, env_del_struct);
			return (0);
		}
		if (!(lst_link = ft_lstnew(env_struct)))
		{
			ft_lstclear(&lst_head, env_del_struct);
			return (0);
		}
		ft_lstadd_back(&lst_head, lst_link);
		i++;
	}
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

/*
**	note:	this function will be called when its necessary to free the list of
**			t_env structs.
*/

void	env_del_struct(void *env)
{
	free(((t_env*)env)->label);
	free(((t_env*)env)->value);
	free((t_env*)env);
}

/*
** note:	This finction will get the string either imported from the env, and
**			sent byt the export function and split it to the first '=' sign
**			found into two elements of a struct: label and value.
** note:	If no '=' is found, label takes str, and value is an empty string.
** RETURN:	t_env *
**			NULL if some malloc failed.
*/

t_env	*env_build(char *str)
{
	t_env *new;
	int i;

	i = 0;
	if (!(new = env_init_struct()))
		return (NULL);
	if ((-1 == (i = ft_strichr(str, '='))))
	{
		if (!(new->label = ft_strdup(str)) || !(new->value = ft_strdup("")))
		{
			free(new);
			return (NULL);
		}
		else
			return (new);
	}
	if (!(new->label = ft_substr(str, 0, i)) \
			|| (!(new->value = ft_substr(str + ++i, 0, ft_strlen(str)))))
	{
		free(new->value);
		free(new->label);
		free(new);
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

t_env *env_init_struct(void)
{
	t_env * new;

	if (!(new = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	new->label = NULL;
	new->value = NULL;
	return (new);
}

/*
** note:	this function will represent the env buit-in facility
*/

void	env_builtin(t_list *env)
{
	while (env)
	{
		ft_putstr_fd(((t_env*)(env->content))->label, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(((t_env*)(env->content))->value, 1);
		env = env->next;
	}
}
