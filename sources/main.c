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

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	char	prompt[] = "\033[32mmy_prompt$\033[m ";
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
		if (!ft_strlen(command) || only_white_spaces(command))
			continue;
		printf("command: |%s|\n", command);
		if (!lexer_root(command))
			printf("lexer_root returned null\n");
		free(command);
	}
	return (0);
}

/*
** note:	this function will discard a command line if there is only spaces.
** RETURN:	1 only white spaces
**			0 elsewise.
*/

int	only_white_spaces(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
/*
parsing:
		INPUT: command line

		1)tokenize_root
			- from left to right.
			- skip spaces.
			- skip quoted sections
			-
		2)categorize tokens.
		3)parse for invalid things.
		4)parse into commands
		5)
*/
