/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 21:26:50 by charmstr          #+#    #+#             */
/*   Updated: 2020/04/13 17:04:00 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	this function will append a char to a string that does not need to
**			be existing. the string is updated and memory of the old string is
**			freed anyway.
**
** RETURN:	1 if OK
**			0 elsewise.
*/

int	ft_strappend(char **str, char c)
{
	char *char_str;

	char_str = (char [2]){c, '\0'};
	if (!*str)
	{
		if (!(*str = ft_strdup(char_str)))
			return (0);
	}
	else if (!(*str = ft_strjoin_free(*str, char_str, 1)))
		return (0);
	return (1);
}
