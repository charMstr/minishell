/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:27:06 by charmstr          #+#    #+#             */
/*   Updated: 2020/01/30 15:48:00 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	this function will make a duplicate of a two dimensional array.
**
** RETURN:	NULL -> failure in malloc or inside ft_strdup.
**			char **fully copied 2d array.
*/

char	**ft_array_dup(char **array)
{
	char	**copy;
	int		i;
	int		height;

	height = 0;
	i = 0;
	if (!array)
		return (NULL);
	while (array[height])
		height++;
	if (!(copy = (char **)malloc(sizeof(char *) * (height + 1))))
		return (NULL);
	copy[height] = NULL;
	while (i < height)
	{
		if (!(copy[i] = ft_strdup(array[i])))
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}
