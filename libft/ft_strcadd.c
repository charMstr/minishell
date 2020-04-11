/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:14:46 by charmstr          #+#    #+#             */
/*   Updated: 2019/10/08 16:31:17 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	This function inserts in a string that does not need to exist, a
**			given character, in a given position.
**			The string is updated and memory of the old string is freed anyway.
**
** input:	- str:	can be NULL
**			- c:	char to inject
**			- i:	index of injection
**
** RETURN:	1 ok
**			0 failure (the string is set to NULL).
*/

int ft_strcadd(char **str, char c, size_t index)
{
	size_t	tt_len;
	char *new;
	size_t	j;

	tt_len = ft_strlen(*str) + 1;
	j = 0;
	if (!(new = (char*)malloc(sizeof(char) * (tt_len + 1))))
	{
		ft_free((void **)str);
		return (0);
	}
	new[tt_len] = '\0';
	while (j < index && j < (tt_len - 1))
	{
		new[j] = str[0][j];
		j++;
	}
	new[j] = c;
	while (++j < tt_len)
		new[j] = str[0][j - 1];
	ft_free((void**)str);
	*str = new;
	return (1);
}
