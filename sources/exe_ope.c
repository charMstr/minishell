/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_ope.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 10:11:48 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 10:11:51 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_sig;

int		exe_and(t_btree *ast, t_control *control)
{
	exe_root(ast->left, control);
	if (control->exit_status == 0)
		exe_root(ast->right, control);
	return (control->exit_status);
}

int		exe_or(t_btree *ast, t_control *control)
{
	exe_root(ast->left, control);
	if (control->exit_status != 0)
		exe_root(ast->right, control);
	return (control->exit_status);
}

int		exe_semi(t_btree *ast, t_control *control)
{
	exe_root(ast->left, control);
	exe_root(ast->right, control);
	return (control->exit_status);
}

int		exe_cmd(t_btree *ast, t_control *control)
{
	if (!exe_simple_cmd_root((t_token *)ast->item, control))
		return (0);
	return (1);
}

int		exe_subshell(t_btree *ast, t_control *control)
{
	pid_t	pid;
	int		status;

	ft_fork(&pid);
	if (pid == 0)
	{
		ft_signalhandler_disable();
		exe_root(ast->left, control);
		exit(control->exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		control->exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : g_sig;
	}
	return (control->exit_status);
}
