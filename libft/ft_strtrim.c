/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 19:26:40 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/12 17:35:01 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** arg1: string to be trimed
** arg2: set of characters to be removed presented as a string
**
** RETURN: trimed string, or NULL if malloc failed or NULL argument was passed.
** note: it can be an empty string returned.
*/

static int	find_start(char const *s1, char const *set)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (set[j] && s1[i])
	{
		if (set[j] == s1[i])
		{
			i++;
			j = 0;
			continue;
		}
		j++;
	}
	return (i);
}

static int	find_end(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		set_length;

	set_length = ft_strlen(set);
	i = ft_strlen(s1) - 1;
	j = set_length - 1;
	while (j >= 0 && i >= 0)
	{
		if (set[j] == s1[i])
		{
			i--;
			j = set_length - 1;
			continue;
		}
		j--;
	}
	return (i);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		number_char;
	int		end;
	int		start;
	int		i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	end = find_end(s1, set);
	start = find_start(s1, set);
	number_char = (end == -1) ? 0 : end - start + 1;
	if (!(ptr = (char *)malloc(sizeof(char) * (number_char) + 1)))
		return (NULL);
	while (i < number_char)
	{
		ptr[i] = s1[start + i];
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
