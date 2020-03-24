/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strichr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 01:47:47 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/19 19:06:09 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	this funciton will look for a char in a string and give the incdex
**			of the very first occurence.
**
**			uefull for checking the presence of a flag in a predefined string.
**
** note2:	see ft_strchr() and strrchr for  a returned pointer.
**
** RETURN:	the index of the first character 'c' found in string 'str'
**			-1 if failure
*/

int	ft_strichr(const char *str, char c)
{
	int index;

	index = 0;
	if (!str)
		return (-1);
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}
