/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 22:09:21 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 17:54:48 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** /!\ do not use
** only does the job if the <dst> pointer is a string way shorter than its
** allocated memory which is <dstsize>, so that there is enough space for <src>
** string to be added if RETURN is bigger than <dstsize> then it means they
** dont fit .
**
** note: use ft_strjoin instead
**
** note2: ioriginal not protected against NULL inputs arguments
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t k;
	size_t src_len;

	i = 0;
	k = 0;
	src_len = 0;
	while (dst[i] && i < dstsize)
		i++;
	while (src[src_len])
		src_len++;
	if (!dstsize)
		return (i + src_len);
	while (src[k] && (i + k < dstsize - 1))
	{
		dst[i + k] = src[k];
		k++;
	}
	if (i + k <= dstsize - 1)
		dst[i + k] = '\0';
	return (i + src_len);
}
