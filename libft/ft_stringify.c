/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:38:12 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/03 01:02:00 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	this function will strigify a string. adding more '\' in front of
**			escape sequences
**
** RETURN:	a malloced string.
**			NULL if failure.
*/

static int	count_escape_sequence(char *str)
{
	int extra_len;
	int len;

	extra_len = 0;
	len = 0;
	if (!str)
		return (-1);
	while (str[len])
	{
		if (str[len] == '\n' || str[len] == '\t' || str[len] == '\\' \
			|| str[len] == '\r' || str[len] == '\b' || str[len] == '\"')
			extra_len++;
		len++;
	}
	return (extra_len + len);
}

char		*ft_stringify(char *line)
{
	char	*new;
	int		lim;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!line)
		return (NULL);
	lim = count_escape_sequence(line);
	if (!(new = (char*)malloc(sizeof(char) * (lim + 1))))
		return (NULL);
	new[lim] = '\0';
	while (++i < lim)
	{
		if (line[++j] == '\n' || line[j] == '\t' || line[j] == '\\' \
			|| line[j] == '\r' || line[j] == '\b' || line[j] == '\"')
		{
			new[i] = '\\';
			new[++i] = line[j];
		}
		else
			new[i] = line[j];
	}
	return (new);
}
