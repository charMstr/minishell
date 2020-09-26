/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 10:08:14 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 20:23:12 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file will be in charge of anything in relation to environment variables
*/

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

/*
** note:	this function update the env variable SHLVL by using export
**			first we seach the current shlvl, then add one and export it
**
** RETURN:	1 OK
**			0 KO
*/

int		env_shlvl_update(t_list **env, t_control *control)
{
	int		shlvl;
	char	*nbr;
	char	*argv[3];

	if (!(nbr = env_get("SHLVL", 5, *env)))
		nbr = "0";
	shlvl = ft_atoi(nbr) + 1;
	argv[0] = "export";
	argv[1] = NULL;
	argv[2] = NULL;
	if (!(nbr = ft_itoa(shlvl)) ||
		!(argv[1] = ft_strjoin_free("SHLVL=", nbr, 2)))
		return (0);
	export_builtin(env, argv, control);
	free(argv[1]);
	return (1);
}
