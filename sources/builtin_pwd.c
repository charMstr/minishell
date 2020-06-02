#include "minishell.h"

/*
** note:	this function will take care of the pwd builtin, the getcwd utility
**			can fail while malloc, in which case the exit_status should be set
**			accordingly, and control->quit should be raised.
**
** note:	free the returned string when done.
**
** RETURN:	1 OK
**			0 KO
*/

int pwd_builtin(t_control *control)
{
	char *pwd;

	if (!(pwd = getcwd(NULL, 0)))
	{
		ft_putstr_fd(strerror(errno), 2);
		control->exit_status = errno;
		control->quit = 1;
		return (0);
	}
	control->exit_status = 0;
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (1);
}
