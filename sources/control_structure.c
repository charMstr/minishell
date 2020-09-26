/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_structure.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 10:08:04 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 19:33:59 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file is in charge of the control structure that will be carried all
** along the main steps of the minishell (at least the input , lexer as a start
*/

/*
** note:	this function will init the t_control struct
*/

int		control_init_struct(t_control *control)
{
	extern char **environ;

	ft_bzero(control, sizeof(*control));
	control->parent_pid = getpid();
	if (!(control->history = history_init_struct()) ||
		!(control->term = terminfo_init_database()) ||
		!(control->env = env_build_linked_list(environ)))
		return (0);
	if (!control_load_start_prompts(&control->env, \
				"\033[93m⚡\033[5;92m mli_&_charmstr \033[0;93m⚡\033[m ", \
				"🍝 > "))
		return (0);
	if (!env_shlvl_update(&control->env, control))
		return (0);
	if (!(control->cwd = getcwd(NULL, 0)))
		return (0);
	if ((control->truefd[STDIN_FILENO] = dup(STDIN_FILENO)) == -1 ||
		(control->truefd[STDOUT_FILENO] = dup(STDOUT_FILENO)) == -1 ||
		(control->truefd[STDERR_FILENO] = dup(STDERR_FILENO)) == -1)
		return (0);
	if (tcgetattr(STDIN_FILENO, &control->termios_default) == -1)
		return (0);
	return (1);
}

/*
** note:	this function will load our special classy PS1 and PS2 into the
**			env variables.
**
** RETURN:	1, OK
**			0, KO. malloc failure.
*/

int		control_load_start_prompts(t_list **env, char *ps1, char *ps2)
{
	unset_in_env_list(env, "PS1");
	unset_in_env_list(env, "PS2");
	if (!export_builtin_new_env("PS1", ps1, env))
		return (0);
	if (!export_builtin_new_env("PS2", ps2, env))
		return (0);
	return (1);
}

/*
** note:	this function is in charge of cleaning everything that was malloced
**			from the stuct, bt not the struct itself.
*/

void	control_free_struct(t_control *control)
{
	terminfo_free_struct(control->term);
	ft_dlstclear(&(control->history->head), history_del_content);
	ft_free((void **)&control->history);
	ft_free((void **)&control->cwd);
	ft_lstclear(&control->env, env_del_struct);
}
