/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:13:25 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/12 18:51:05 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** /!\ original function not protected against passing NULL args
**
** note: no use of malloc here
** RETURN: pointer in which is copied len bytes from src to dst*
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	i = 0;
	if (len != 0 && !dst && !src)
		return (dst);
	while (i < len)
	{
		if (dst > src)
			*((char *)dst + len - i - 1) = *((char *)src + len - i - 1);
		else
			*((char *)dst + i) = *((char *)src + i);
		i++;
	}
	return (dst);
}
