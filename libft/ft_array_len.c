/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:27:06 by charmstr          #+#    #+#             */
/*   Updated: 2020/01/30 15:48:00 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	this function will return the length of a two dimension chararray
**
** RETURN:	-1 if array itself is NULL
**			0 the first string was NULL
**			>0 for the number of substrings non NULL
*/

int	ft_array_len(char **array)
{
	int i;

	i = 0;
	if (!array)
		return (-1);
	while (array[i])
	{
		i++;
	}
	return (i);
}
