/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:22:12 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/09 18:20:28 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** /!\ the pointer is not protected if NULL in the original function
**
** note: use ft_strchr if you want to search from begining
**
** RETURN: the location of the last c character in the string, or NULL pointer
*/

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int position;

	position = -1;
	i = 0;
	if (!s)
		return (NULL);
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			position = i;
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	else if (position >= 0)
		return ((char *)(s + position));
	else
		return (NULL);
}
