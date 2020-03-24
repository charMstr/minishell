/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:46:48 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/11 21:07:52 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** /!\ the original is not protected against passing a null pointer as arg
**
** RETURN: a new pointer freshly malloced, copy of s1, or NULL if failed
*/

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	i = 0;
	len = ft_strlen(s1);
	if (!(ptr = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		*(ptr + i) = *(s1 + i);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
