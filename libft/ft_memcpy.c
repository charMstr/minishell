/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:44:56 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/12 18:49:17 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** /!\ the original function does segfault when arg pointers are NULL.
**
** /!\ use ft_memmove instead, as the overlapping of memory areas result in
** an undefined behavior
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (n != 0 && !dst && !src)
		return (dst);
	while (i < n)
	{
		*((unsigned char *)dst + i) = *((const unsigned char *)src + i);
		i++;
	}
	return (dst);
}
