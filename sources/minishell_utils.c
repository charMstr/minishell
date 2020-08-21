/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:31:06 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 11:31:07 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file will contain functions helpful that helps with packing up some
** lines and have a less redundant code.
*/

/*
** note: this function does fill in the pointer to an int table of two fd.
*/

void	ft_pipe(int (*fildes)[2])
{
	if (pipe(*fildes) == -1)
		ft_exit("pipe", NULL, strerror(errno), EXIT_FAILURE);
}

/*
** note:	this function will fork and the child will be the process in which
**			the pid value is equal to zero.
** note:	this fork raises errno to `22 : Invalid argument`
**			thus errno = 0 to fix it
*/

void	ft_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		ft_exit("fork", NULL, strerror(errno), EXIT_FAILURE);
	errno = 0;
}

/*
** note:	this function will create a pipe, then do a fork, all that in one
**			using the dedicated struct.
*/

void	ft_fork_pipe(t_pipe *pipe)
{
	ft_pipe(&(pipe->fildes));
	ft_fork(&(pipe->pid));
}

/*
** note:	this one liner will call strerror and exit, all at once.
*/

void	ft_exit(char *cmd, char *param, char *str, int status)
{
	ft_perror(cmd, param, str);
	exit(status);
}

/*
** cmd and param gives additional (&& optional) details
** str describs the error || is strerror(errno) if NULL is given && errno is set
*/

int		ft_perror(char *cmd, char *param, char *str)
{
	const int fd = STDERR_FILENO;

	ft_putstr_fd("\033[0;91m", fd);
	ft_putstr_fd("minishell: ", fd);
	if (cmd)
	{
		ft_putstr_fd(cmd, fd);
		ft_putstr_fd(": ", fd);
	}
	if (param)
	{
		ft_putstr_fd("`", fd);
		ft_putstr_fd(param, fd);
		ft_putstr_fd("': ", fd);
	}
	if (errno && !str)
		str = strerror(errno);
	if (str)
	{
		ft_putstr_fd("Error: ", fd);
		ft_putendl_fd(str, fd);
	}
	ft_putstr_fd("\033[0m", fd);
	return (-1);
}

/*
** note:	this function will simply display a messae when there is an
**			ambiguous redirection attempted in a single command:
**			redirection in a $VAR that happens to be empty.
**			redirection in a filename that becomes mutliple tokens after either
**			field splitting, or pathname expansion(kleen star operator).
*/

void	ft_ambiguous_redirect(char *str, int fd)
{
	ft_putstr_fd("\033[0;91m", fd);
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(": ambiguous redirect\n", fd);
	ft_putstr_fd("\033[0m", fd);
}
