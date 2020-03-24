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
** /!\ arguments are not protected against NULL pointers in original
**
** note: characters after a '\0' wont be compared
**
** if you want to make sure both strings are 100% different -->  should be used
** with <n> as ft_strlen(smallest string) + 1
**
** RETURN: no difference -> 0. compares until index (n - 1)
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
