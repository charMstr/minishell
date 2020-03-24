#include "minishell.h"

/*
** This file is the root file for getting a command from the standard input.
**
** The way we implement it and why:
**
**	WHY:
** when for expample "sleep 3" is run while its running, the next user's input
** are being recorded. if the ctrl+C is hit meanwhile, then the new prompt is
** written, and the user's input is lost.
**
**	IMPLEMENTATION:
** fork is done. The child will read from the standard input, one character
** after another, and redirect through a pipe to the parent process.
** if Ctrl+C is hit (SIG_INT), then the signal handler in the child process
** will kill the child.
** if the child gets a '\n', then its over for him as well.
*/

/*
** note:	this function will returN the command that was entered in the input
**			of the minishell.
** RETURN:	the command that ended by a '\n'
** 			NULL if the ctrl+C was caught in the child.
*/

char *get_next_command(int *quit)
{
	char *command;
	t_mysh mini;

	ft_fork_pipe(&mini);
	if (mini.pid == 0)
	{
		close(mini.pipe[0]);
		child_get_next_command(mini.pipe[1]);
	}
	close(mini.pipe[1]);
	command = collect_char_by_char(mini.pipe[0]);
	waitpid(mini.pid, &(mini.stat_loc), WUNTRACED);
	if (WIFEXITED(mini.stat_loc))
	{
		//printf("\n===> the child process exited normally\n");
		//printf("the exit status was: %d\n", (int)WEXITSTATUS(mini.stat_loc));
		//printf("the command is :[%s]\n", command);
		if ((int)WEXITSTATUS(mini.stat_loc) == 2)
			*quit = 1;
		return (command);
	}
	if (WIFSIGNALED(mini.stat_loc))
	{
		//printf("\n==> killed by a signal, signal ID was: %d\n", (int)WTERMSIG(mini.stat_loc));
		return (NULL);
	}
	return (NULL);
}

/*
** note:	this child func will read on stdin, char by char, and transfer them
**			to its parent process.
**
** note:	we reset the default behaviour relative to SIGINT signal.
**
** exit:	EXIT_FAILURE if read failed.
**			EXIT_SUCCESS if the ENTER was hit.
**			2 if the ctrl_D special character was sent.
*/

void	child_get_next_command(int fd_w)
{
	char buff;
	int res;

	signal(SIGINT, SIG_DFL);
	while ((res = read(STDIN_FILENO, &buff, 1)) > 0)
	{
		if (buff == '\n')
			break;
		write(fd_w, &buff, res);
	}
	if (res == -1)
		exit(EXIT_FAILURE);
	if (res == 0)
		exit(2);
	exit(EXIT_SUCCESS);
}

/*
** note:	this function belongs to the parent process (minishell), it will
**			get char after char from the spawned child to will get the command.
**
** RETURN:	NULL if (malloc failed)
**			char *, the command with all the appended characters.
*/

char *collect_char_by_char(int fd_r)
{
	char buff[BUFFER_SIZE + 1];
	char *cmd;
	char *tmp;
	int res;

	if (!(cmd = ft_strdup("")))
		return (NULL);
	while ((res = read(fd_r, buff, BUFFER_SIZE)) > 0)
	{
		buff[res] = '\0';
		tmp = ft_strjoin(cmd, buff);
		free(cmd);
		if (!tmp)
			ft_perror("malloc", EXIT_FAILURE);
		cmd = tmp;
	}
	if (res == -1)
		ft_perror("read", EXIT_FAILURE);
	return (cmd);
}
