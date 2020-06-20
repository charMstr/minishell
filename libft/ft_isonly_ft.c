/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isonly_ft.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 22:00:24 by mli               #+#    #+#             */
/*   Updated: 2020/06/20 22:03:26 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	tells if the string contains only one type of character
**          according to a function (i.e. ft_isalpha/alnum/...)
**
** usage:	It will make sure there is at least (if strict is != 0)
**			one character and that all characters in the string are the same
**			char or not.
**			If 'strict' is disabled, NULL/empty string will return true.
**
** RETURN:	0 KO
**			1 OK
*/

int	ft_isonly_ft(char *str, int (*ft_issmth)(int c), int strict)
{
	int i;

	i = -1;
	if (!str || !str[0])
		return (strict ? 0 : 1);
	while (str[++i])
		if (!ft_issmth(str[i]))
			return (0);
	return (1);
}
