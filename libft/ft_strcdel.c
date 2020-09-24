/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:14:46 by charmstr          #+#    #+#             */
/*   Updated: 2020/08/21 09:40:06 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	this function will delete a char in a given postion within a string
** note:	if the string is empty or null we just exit.
**			if the index is too big, nothing is changed in the current string.
**			otherwise the string is collapsed onto itself at the position of
**			the char with a memmove.
**
** input:	- str
**			- the index of the char to be deleted
*/

void	ft_strcdel(char *str, size_t i)
{
	size_t	len;

	if (!str || !ft_strlen(str))
		return ;
	len = ft_strlen(str);
	if (i >= len)
		return ;
	ft_memmove(str + i, str + i + 1, len - i);
}
