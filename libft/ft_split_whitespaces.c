/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 21:26:50 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/13 23:05:05 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	this function is like a ft_split, except that it uses a set of char
**			in the ifs parameter (internal field separator, like in shell doc).
**
** RETURN:	char **
**			NULL if failure or NULL inputs
*/

static int	find_start(char const *s, char *ifs, int next_start)
{
	while (s[next_start] && (ft_strichr(ifs, s[next_start]) != -1))
		next_start++;
	return (next_start);
}

static int	find_end(char const *s, char *ifs, int next_end)
{
	while (s[next_end] && (ft_strichr(ifs, s[next_end]) != -1))
		next_end++;
	while (s[next_end] && (ft_strichr(ifs, s[next_end]) == -1))
		next_end++;
	return (next_end);
}

static int	size_array(char const *s, char *ifs)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && (-1 != ft_strichr(ifs, s[i])))
			i++;
		if (s[i] && (ft_strichr(ifs, s[i]) == -1))
			count++;
		while (s[i] && (ft_strichr(ifs, s[i]) == -1))
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

char		**ft_split_whitespaces(char const *s, char *ifs)
{
	char	**ptr;
	int		i;
	int		k;
	int		j;
	int		size;

	i = 0;
	k = 0;
	if (!s || !ifs ||
			!(ptr = (char **)malloc(sizeof(char*) * (size_array(s, ifs) + 1))))
		return (NULL);
	size = size_array(s, ifs);
	ptr[size] = NULL;
	while (k < size)
	{
		i = find_start(s, ifs, i);
		if (!(ptr[k] = (char *)malloc(sizeof(char) * (find_end(s, ifs, i) - i \
							+ 1))))
			return (free_nested(ptr, k));
		j = 0;
		while (s[i] && (-1 == ft_strichr(ifs, s[i])))
			ptr[k][j++] = s[i++];
		ptr[k++][j] = '\0';
	}
	return (ptr);
}
