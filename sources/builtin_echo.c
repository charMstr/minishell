#include "minishell.h"

/*
** this file is a subset of the the builtin_root.c file.
** this file will take care of the builtin echo
*/

/*
** note:	this implementation of the echo builtin only takes one option:
**			the -n.
** note:	we assume the argv[0] is the name of the utility.
** note:	the exit_status is always set to zero.
**
** RETURN:	1 on success always.
*/

int	echo_builtin(char **argv, t_control *control)
{
	int i;
	int n_option;

	i = 1;
	while (argv[i] && argv[i][0] == '-' && ft_isonly(argv[i] + 1, 'n'))
		i++;
	n_option = (i == 1 ? 0 : 1);
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[++i])
			ft_putchar_fd(' ', 1);
	}
	if (!n_option)
		ft_putchar_fd('\n', 1);
	control->exit_status = 0;
	return (1);
}
