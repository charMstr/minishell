/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 10:03:44 by mli               #+#    #+#             */
/*   Updated: 2020/09/29 11:27:49 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	alpha_cmp(const t_env *const s1, const t_env *const s2)
{
	int cmp;

	if (!s2)
		return (-1);
	cmp = ft_strcmp(s1->label, s2->label);
	return (cmp);
}

static void	export_no_arg_display(const t_env *env)
{
	const char		*str = "declare -x ";

	ft_putstr_fd((char *)str, 1);
	ft_putstr_fd(env->label, 1);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(env->value, 1);
	ft_putendl_fd("\"", 1);
}

static void	export_builtin_no_arg_end(t_list const *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->content;
		tmp->tmpdeclare = 0;
		env = env->next;
	}
}

void		export_builtin_no_arg(t_list **head, t_control *control)
{
	const t_list	*env = *head;
	t_env			*tmp;
	t_env			*sort;
	int				list_size;

	control->exit_status = 0;
	list_size = ft_lstsize(*head);
	while (list_size--)
	{
		env = *head;
		sort = NULL;
		while (env)
		{
			tmp = env->content;
			if (tmp->tmpdeclare == 0 && alpha_cmp(tmp, sort) < 0)
				sort = tmp;
			env = env->next;
		}
		if (sort && sort->tmpdeclare == 0)
		{
			export_no_arg_display(sort);
			sort->tmpdeclare = 1;
		}
	}
	export_builtin_no_arg_end(*head);
}
