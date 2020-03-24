/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 18:55:09 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/11 21:08:34 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** /!\ the pointer is not protected if NULL in the original function
**
** note: use ft_strrchr if you want to search from the end
**
** RETURN: the location of character c in the string, else NULL pointer
*/

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	else
		return (NULL);
}
