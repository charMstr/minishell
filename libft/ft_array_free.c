/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:30:31 by charmstr          #+#    #+#             */
/*   Updated: 2020/08/21 09:37:08 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	this function will free a two dimensional char array.
** input:	- ptr:	the two dimension array to be freed,
**			- k:	the index from wich to start decreasing.
**
** exemple:	ft_array_free(array, ft_array_len(array));
**
** RETURN:	NULL for context convenience
*/

void	*ft_array_free(char **ptr, int k)
{
	if (!ptr)
		return (NULL);
	while (--k >= 0)
	{
		free(ptr[k]);
		ptr[k] = NULL;
	}
	free(ptr);
	ptr = NULL;
	return (NULL);
}
