/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 10:28:08 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 19:29:49 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** note:	this function will initialise the line discipline of the terminal
**			through the struct termios.
** note:	this function saves in old pointer the previous settings.
**
** RETURN:	0 if faillure
**			1 OK
*/

static int	termios_getattr(t_control *control, struct termios *term)
{
	if (tcgetattr(STDIN_FILENO, term) == -1)
	{
		control->quit = 1;
		control->exit_status = 1;
		ft_perror("tcgetattr can't get", NULL, strerror(errno));
		return (0);
	}
	return (1);
}

static int	termios_setattr(t_control *control, struct termios *term)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, term) == -1)
	{
		control->quit = 1;
		control->exit_status = 1;
		ft_perror("tcsetattr can't set", NULL, strerror(errno));
		return (0);
	}
	return (1);
}

int			termios_enable_raw_mode(t_control *control, struct termios *old)
{
	struct termios new;
	struct termios current;

	if (termios_getattr(control, &current) == 0)
		return (0);
	new = *old;
	new.c_iflag &= ~(IXON);
	new.c_lflag &= ~(ECHO);
	new.c_lflag &= ~(ECHOCTL);
	new.c_lflag &= ~(ICANON);
	new.c_lflag &= ~(ISIG);
	new.c_cc[VTIME] = 1;
	new.c_cc[VMIN] = 0;
	if (!ft_memcmp(&current, &new, sizeof(struct termios)))
		return (1);
	if (termios_setattr(control, &new) == 0)
		return (0);
	return (1);
}

int			termios_reset_cooked_mode(t_control *control, \
		struct termios *saved_copy)
{
	struct termios new;

	if (termios_getattr(control, &new) == 0)
		return (0);
	if (!ft_memcmp(saved_copy, &new, sizeof(struct termios)))
		return (1);
	if (termios_setattr(control, saved_copy) == 0)
		return (0);
	return (1);
}
