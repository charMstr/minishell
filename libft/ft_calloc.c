/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:32:37 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/11 21:09:53 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*
** ARGS: the number of elements (+/- '\0' if strings..), then sizeof(*...)
**
** RETURN: pointer NULL if failed --> always test when calling this function
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	if (!(ptr = (void *)malloc(count * size)))
		return (NULL);
	else
		while (i < size * count)
		{
			*((unsigned char *)ptr + i) = 0;
			i++;
		}
	return (ptr);
}
