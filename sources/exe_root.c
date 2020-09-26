/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:52:22 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 19:36:58 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file is the root file for the execution of the minishell commands. The
** start point is the ast, a binary tree whose nodes->item are tokens.
*/

/*
** note: this function will be the starting point for interpreting the ast.
** it will be called recursively
*/

const t_exe *g_exec = (const t_exe	[]){{AND_IF, exe_and}, {OR_IF, exe_or},
	{PIPE, exe_pipe}, {LIST, exe_cmd}, {SEMI, exe_semi}, {-1, exe_semi},
	{SUBSHELL, exe_subshell},
	{0, NULL}};

void	exe_root(t_btree *ast, t_control *control)
{
	int i;
	int current_id;

	if (!ast || control->quit)
		return ;
	i = 0;
	current_id = btree_id(ast);
	while (g_exec[i].fct != NULL && g_exec[i].id != current_id)
		i++;
	if (g_exec[i].fct)
		g_exec[i].fct(ast, control);
}

void	ft_errno_exit(void)
{
	if (errno == 13)
		exit(126);
	exit(1);
}
