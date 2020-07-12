/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 19:03:20 by mli               #+#    #+#             */
/*   Updated: 2020/07/12 17:31:05 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_sig;

/*
** note:	Here you can find the function run when a signal is intercepted
*/

void	ft_sigquit(int sig)
{
	ft_putstr_fd("Quit : ", 2);
	ft_putnbr_fd(sig, 2);
	ft_putchar_fd('\n', 2);
	g_sig = SIGCAUGHT + sig;
}

void	ft_sigint(int sig)
{
	ft_putchar_fd('\n', 2);
	g_sig = SIGCAUGHT + sig;
}

/*
** Change signals' behaviours
*/

void	ft_signalhandler_enable(void)
{
	signal(SIGQUIT, ft_sigquit);
	signal(SIGINT, ft_sigint);
}

/*
** Signals' behaviours returned to default
*/

void	ft_signalhandler_disable(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
