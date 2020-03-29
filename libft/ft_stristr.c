#include "libft.h"

/*
** note:	this function reuses the ft_strichr function, and uses the same
**			concept, except that we are looking for the presence of any char
**			amongst a string of characters.
**
** RETURN:	The index of the first character found in string 'str', from string
**			stack.
**			-1 if failure
*/

int	ft_stristr(const char *str, char *stack)
{
	int i;
	int j;

	if (!str || !stack)
		return (-1);
	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (stack[j])
		{
			if (str[i] == stack[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}
