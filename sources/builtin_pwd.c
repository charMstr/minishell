#include "minishell.h"

/*
** note:	this function will take care of the pwd builtin,
**			it should never fail so we use a variable updated by cd
**			and not getcwd()
**			ex : mkdir test && cd test && rmdir ../test && pwd
**
** RETURN:	1 OK
*/

int pwd_builtin(t_control *control)
{
	control->exit_status = 0;
	ft_putendl_fd(control->cwd, 1);
	return (1);
}
