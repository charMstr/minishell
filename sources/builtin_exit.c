/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 22:22:22 by mli               #+#    #+#             */
/*   Updated: 2020/09/28 14:23:31 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exit_builtin(char **argv, t_control *control)
{
	int has_sign;

	control->quit = 1;
	if (control->parent_pid == getpid())
		ft_putendl_fd("exit", 2);
	if (!argv || !argv[1])
		return (1);
	has_sign = (argv[1][0] == '-' || argv[1][0] == '+' ? 1 : 0);
	if (!ft_isonly_ft(argv[1] + has_sign, ft_isdigit, 1))
	{
		ft_perror("exit", argv[1], "numeric argument required");
		control->exit_status = 255;
	}
	else if (ft_array_len(argv) >= 3)
	{
		ft_perror("exit", NULL, "too many arguments");
		control->quit = 0;
		control->exit_status = 1;
	}
	else
		control->exit_status = (unsigned char)ft_atoi(argv[1]);
	return (1);
}
