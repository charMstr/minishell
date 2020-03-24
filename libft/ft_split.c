/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 21:26:50 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/13 23:05:05 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note: use of malloc, and free
**
** RETURN: the array of strings separated by c, or NULL if malloc failed or if
** empty string
*/

static int	find_start(char const *s, char c, int next_start)
{
	while (s[next_start] && s[next_start] == c)
		next_start++;
	return (next_start);
}

static int	find_end(char const *s, char c, int next_end)
{
	while (s[next_end] && s[next_end] == c)
		next_end++;
	while (s[next_end] && s[next_end] != c)
		next_end++;
	return (next_end);
}

static int	size_array(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static void	*free_nested(char **ptr, int k)
{
	while (--k >= 0)
	{
		free(ptr[k]);
		ptr[k] = NULL;
	}
	free(ptr);
	ptr = NULL;
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
	int		k;
	int		j;

	i = 0;
	k = 0;
	if (!s || !(ptr = (char **)malloc(sizeof(char*) * (size_array(s, c) + 1))))
		return (NULL);
	ptr[size_array(s, c)] = NULL;
	while (k < size_array(s, c))
	{
		i = find_start(s, c, i);
		if (!(ptr[k] = (char *)malloc(sizeof(char) * (find_end(s, c, i) - i \
							+ 1))))
			return (free_nested(ptr, k));
		j = 0;
		while (s[i] && s[i] != c)
			ptr[k][j++] = s[i++];
		ptr[k][j] = '\0';
		k++;
	}
	return (ptr);
}
