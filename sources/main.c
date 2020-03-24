#include "minishell.h"

/*
** note:	this Main will display a prompt, get the command and then send then
**			to a subfunction which will parse, then execute the commands in
**			subprocesses.
**			the sunfunction will Return the exit status. (the one we get with
**			"echo $?").
**
** RETURN:	this function should never do so.
**			the only way to exit is with the exit builtin, or when hitting
**			ctrl+D and there is nothing at all to be read on the stdin.
*/

//remove the args to the Main...
int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	char	prompt[] = "my_prompt$ ";
	char	*command;
	int		quit;

	signal(SIGINT,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
	quit = 0;
	while (1)
	{
		ft_putstr_fd(prompt, STDOUT_FILENO);
		if (!(command = get_next_command(&quit)))
			continue;
		if (quit == 1)
		{
			free(command);
			exit(0);
		}
		process_commands(command);
		free(command);
	}
	return (0);
}
