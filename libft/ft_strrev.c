/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:25:14 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/13 16:44:55 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	This function reverses all the characters of a string.
**			No new string is created.
*/

char	*ft_strrev(char *str)
{
	int		i;
	int		j;

	if (!str)
		return (NULL);
	j = 0;
	i = ft_strlen(str) - 1;
	while (i > j)
	{
		str[j] ^= str[i];
		str[i] ^= str[j];
		str[j] ^= str[i];
		j++;
		i--;
	}
	return (str);
}
