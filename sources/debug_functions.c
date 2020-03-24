#include "debug.h"

void	debug_pars_split_commands(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_putendl_fd(tab[i], 2);
		i++;
	}
}
