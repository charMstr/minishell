/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_perform_arrow.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:51:46 by mli               #+#    #+#             */
/*   Updated: 2020/09/28 14:08:58 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Here are performed redirections and indirections
*/

int	exe_perform_arrow(t_simple_cmd *cmd, t_control *control)
{
	t_list const	*arrows = cmd->arrows;
	t_arrow			*arrow;

	while (arrows && (arrow = arrows->content))
	{
		if ((arrow->id != LESS && !exe_perform_redirections(arrow, control)) ||
			(arrow->id == LESS && !exe_perform_indirections(arrow, control)))
		{
			control->exit_status = 1;
			return (0);
		}
		arrows = arrows->next;
	}
	return (1);
}

int	exe_perform_redirections(t_arrow *arrow, t_control *control)
{
	int			fd;
	int			src;
	int			options;
	const int	signals = S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR;

	src = ft_isdigit(arrow->src[0]) ? ft_atoi(arrow->src) : 1;
	options = (arrow->id == GREAT ? O_TRUNC : O_APPEND);
	if ((fd = open(arrow->dest, O_WRONLY | O_CREAT | options, signals)) < 0)
	{
		ft_perror("open", arrow->dest, strerror(errno));
		return (0);
	}
	if (dup2(fd, src) == -1)
	{
		ft_perror("dup2", NULL, NULL);
		control->quit = 1;
		close(fd);
		return (0);
	}
	return (1);
}

int	exe_perform_indirections(t_arrow *arrow, t_control *control)
{
	int		fd;
	int		src;

	src = ft_isdigit(arrow->src[0]) ? ft_atoi(arrow->src) : 0;
	if ((fd = open(arrow->dest, O_RDONLY)) < 0)
	{
		ft_perror("open", arrow->dest, strerror(errno));
		return (0);
	}
	if (dup2(fd, src) == -1)
	{
		ft_perror("dup2", NULL, NULL);
		control->quit = 1;
		close(fd);
		return (0);
	}
	return (1);
}

int	exe_cancel_arrows(t_control *control)
{
	if ((dup2(control->truefd[STDIN_FILENO], STDIN_FILENO)) == -1 ||
		(dup2(control->truefd[STDOUT_FILENO], STDOUT_FILENO)) == -1 ||
		(dup2(control->truefd[STDERR_FILENO], STDERR_FILENO)) == -1)
	{
		control->quit = 1;
		control->exit_status = 1;
		ft_perror("dup2", NULL, strerror(errno));
		return (0);
	}
	return (1);
}
