/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:23:04 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/12 16:23:07 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	/!\ arguments are not protected against NULL pointers in original
** note:	characters after a '\0' wont be compared
** note:	To make sure both strings are 100% different: it should be used
**			with <n> as ft_strlen(smallest string) + 1
**			So just add a plus one no matter what to ft_strlen(str1/2) to have
**			a standard strcmp behavior.
**
** some example:
**		str1: abcd
**		str2: abcde
**		now doing the call: ft_strncmp(str1, str2, ft_strlen(str1));
**		--> result = 0
**		now doing the call: ft_strncmp(str1, str2, ft_strlen(str1) + 1);
**		--> result != 0
**
** RETURN:	0	-> equal (compares until index (n - 1))
**			!0	-> different
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!n)
		return (0);
	while ((s1[i] == s2[i]) && s1[i] && s2[i] && (i + 1 < n))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
