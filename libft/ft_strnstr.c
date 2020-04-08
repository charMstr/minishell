/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 13:25:49 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/11 21:06:23 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** /!\ original function isn't protected against NULL pointer inputs.
**
** RETURN:	address of the start of the string needle if found in haystack
**			else NULL
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (!needle[0])
	{
		return ((char *)haystack);
	}
	while (haystack[i] && (i < len))
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while ((i + j < len) && haystack[i + j] && needle[j] \
					&& *(haystack + i + j) == *(needle + j))
				j++;
			if (*(needle + j) == '\0')
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
