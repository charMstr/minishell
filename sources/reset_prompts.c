/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_prompts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 13:09:58 by charmstr          #+#    #+#             */
/*   Updated: 2020/09/26 14:21:33 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** note:	this function will check the value of PS1 and PS2 in the env
**			variables.
**			If they have changed, the control->term->prompt_ps1 or ps2 should
**			duplicate those new strings.
**
** RETURN:	1 OK
**			0 KO, malloc failure.
*/

int	reset_prompts(t_list *env, t_term *term)
{
	char	**ps1;
	char	**ps2;

	ps2 = env_get_addr("PS2", 3, env);
	ps1 = env_get_addr("PS1", 3, env);
	if (!reset_prompt(ps1, &term->ps1))
		return (0);
	return (reset_prompt(ps2, &term->ps2));
}

/*
** note:	this function will update the term->ps1 or term->ps2.
**
** RETURN:	1 OK
**			0 KO, malloc failure.
*/

int	reset_prompt(char **ref_from_env, char **term_ps)
{
	if (!ref_from_env || !*ref_from_env)
	{
		if (!*term_ps || !ft_strlen(*term_ps))
		{
			ft_free((void **)term_ps);
			if (!(*term_ps = ft_strdup("")))
				return (0);
		}
	}
	else if (!*term_ps || ft_strcmp(*ref_from_env, *term_ps))
	{
		ft_free((void **)term_ps);
		if (!(*term_ps = ft_strdup(*ref_from_env)))
			return (0);
	}
	return (1);
}
