/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:31:06 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 20:20:39 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this file will contain functions helpful that helps with packing up some
** lines and have a less redundant code.
*/

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
