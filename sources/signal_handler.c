/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 19:03:20 by mli               #+#    #+#             */
/*   Updated: 2020/06/20 19:30:18 by mli              ###   ########.fr       */
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
