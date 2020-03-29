#include "minishell.h"

/*
** this file is the root file that will dispatch the work from an input line to
** the shell.
** it will:
**	-	check if there is no multiline commands. (non matching apostrophes)
**	-	check if there is more than one command (';') and split accordingly.
**	-	in the separated_commands if there are atomic_commands pipelined it
**		will split accordingly
**	-	in each command it will parse it and run a subprocess for each program
**		called.
*/

/*
** note:	This function will check if there is some pending multiline.
**			Then it will split the comand line if there is ';'.
**			Each commands will be run one after another sequentialy in a
**			sufunction.
** note:	the very last command run will return its exit status so that we
**			update the environment variable.
** RETURN:	none.
*/

void	process_commands(char *line)
{
	char **separated_runs;
	int	exit_status;

	printf("line = %s\n",line);
	if (!pars_no_multiline(line))
	{
		ft_putstr_fd("\ninvalid command (multi-line is a bonus!)\n", 1);
		return ;
	}
	if (!(separated_runs = pars_split_commands(line, ';')))
	{
		free(line);
		ft_perror("malloc", EXIT_FAILURE);
	}
	debug_pars_split_commands(separated_runs);
	exit_status = run_separated_commands(separated_runs);
	//at this stage if (the exit status was -1) it means the malloc failed
	//so we need to just exist the whole program after freeing memory.
	ft_free_2d(separated_runs);
	//set_exit_status();
}

/*
** note:	this function will process the commands one by one, SEQUENCIALLY.
**
** RETURN:	the exit status from the last command run.
**			early return if the parsing found some problem. unexpected tokens..
*/

int	run_separated_commands(char **tab)
{
	int i;
	int res_parsing;

	if ((res_parsing = pars_separated_runs_array(tab)))
		return (res_parsing);
	i = 0;
	return (0);
}

