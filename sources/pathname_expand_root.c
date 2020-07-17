#include "minishell.h"

/*
** this is the root file for pathname expansion. While expanding path names, if
** a '*' is quoted, it is not expanded.
** When trying to match a string, its "unquoted equivalent" is used to attempt
** matching a pathname. unquoted equivalent in the sens that the string has not
** been processed for unquoting yet. but we sort of forecast and apply rules as
** if the quoting had already been removed.
*/


/*
** root func for the pathname expansion

// UPDATE ME
** RETURN:	1 OK
**			0 KO
*/

int pathname_expand_root(char *str)
{
	char ref[] = "salut";
	int res;

	res = match_no_star(ref, str, 0, 0);
	(void)res;
	return (1);
}

//	printf("for [%s] & [%s], res is %d\n", ref, str, res);
