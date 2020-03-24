/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 20:16:31 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/12 18:11:43 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** /!\ undefined behavior if strings overlap
** /!\ original function not protected against a NULL pointer argument
**
** note: use ft_strdup insted: it will creat the pointer and malloc it for you
**
** RETURN: the length of the string it tried to create, therefore: strlen(src)
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t src_len;

	if (!src || !dst)
		return (0);
	src_len = ft_strlen(src);
	i = 0;
	if (!dstsize)
		return (src_len);
	while (i < (dstsize - 1) && i < src_len)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	return (ft_strlen(src));
}
