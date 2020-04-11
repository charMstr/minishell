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
** note:	this function will delete a char in a given postion within a string
** note:	if the string is empty its okay. if the index is too big, nothing
**			is changed in the current string.
**			in case of failuer the str is set to null.
**
** input:	- str
**			- the index of the char to be deleted
**
** RETURN:	1 ok
**			0 failure (malloc failed or str was NULL)
*/

int	ft_strcdel(char **str, size_t i)
{
	char	*new;
	size_t	len;

	if (!str || !(*str))
		return (0);
	len = ft_strlen(*str);
	if (i >= len)
		i = len;
	str[0][i] = '\0';
	if (!(new = ft_strjoin(*str, *str + i + 1)))
	{
		ft_free((void**)str);
		return (0);
	}
	ft_free((void**)str);
	*str = new;
	return (1);
}
