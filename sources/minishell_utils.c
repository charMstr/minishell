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
		ft_perror("pipe", EXIT_FAILURE);
}

/*
** note:	this function will fork and the child will be the process in which
**			the pid value is equal to zero.
*/

void	ft_fork(int *pid)
{
	*pid = (int)fork();
	if (*pid == -1)
		ft_perror("fork", EXIT_FAILURE);
}

/*
** note:	this function will create a pipe, then do a fork, all that in one
**			using the dedicated struct.
*/

void	ft_fork_pipe(t_mysh *mini)
{
	ft_pipe(&(mini->pipe));
	ft_fork(&(mini->pid));
}

/*
** note:	this one liner will call perror and exit, all at once.
*/

void	ft_perror(char *str, int status)
{
	perror(str);
	exit(status);
}

//maybe remove me?
void	ft_exit(char *str, int status)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit(status);
}

/*
** RETURN:	the length of a two dimensions array, char **.
**
** note:	if 0 is returned, then the array is empty (first raw is NULL)
**			if -1 is returned , then the array itself is NULL /!\
*/

int	len_2d(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
