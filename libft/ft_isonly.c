/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isonly.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:03:17 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/09 18:07:09 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	tells if the string contains only one type of character.
** note:	if string is empty, only c == '\0' will return 1
**
** usage:	if (str[i] && ft_isonly(str, '*')) will make sure there is at least
**			one character and that all characters in the string are the same
**			char or not.
**
** RETURN:	0 KO, or NULL input
**			1 OK
*/

int	ft_isonly(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (!str[0])
	{
		if (c == '\0')
			return (1);
		else
			return (0);
	}
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}
