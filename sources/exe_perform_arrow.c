#include "minishell.h"

/*
** Here are performed redirections and indirections
*/

int	exe_perform_arrow(t_simple_cmd *cmd, t_control *control)
{
	if (!exe_perform_redirections(cmd->redirections, control) ||
		!exe_perform_indirections(cmd->indirections, control))
	{
		control->exit_status = 1;
		return (0);
	}
	return (1);
}

int	exe_perform_redirections(t_list *redirections, t_control *control)
{
	int			fd;
	int			src;
	int			options;
	const int	signals = S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR;
	t_arrow 	*arrow;

	while (redirections && (arrow = redirections->content))
	{
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
		redirections = redirections->next;
	}
	return (1);
}

int	exe_perform_indirections(t_list *indirections, t_control *control)
{
	int		fd;
	int		src;
	t_arrow *arrow;

	while (indirections && (arrow = indirections->content))
	{
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
		indirections = indirections->next;
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
