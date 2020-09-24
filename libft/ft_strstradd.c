/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstradd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:06:58 by charmstr          #+#    #+#             */
/*   Updated: 2020/08/21 09:40:29 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	This function will insert src in dst starting from start index.
**          Wathever is on the start index and after will be found appended at
**			the end of dst(beginning) + src.
**
** note:	*dst does not need to exist: if NULL, it is made a duplicate of src
** note:	if start is > to *dst len, we just join the two strings.
** note:	*dst is updated anyway, and freed anyway.
**
** RETURN:	0 failure (if !dst or !src or malloc failure)
**			1 ok
*/

static int	ft_strstradd_assist(char **dst, int start, char *src)
{
	char *new;

	if (!(new = ft_substr(*dst, 0, start)))
		return (0);
	if (!(new = ft_strjoin_free(new, src, 1)))
		return (0);
	if (!(new = ft_strjoin_free(new, *dst + start, 1)))
		return (0);
	ft_free((void**)dst);
	*dst = new;
	return (1);
}

int			ft_strstradd(char **dst, int start, char *src)
{
	int len;

	if (!dst || !src)
	{
		ft_free((void**)dst);
		return (0);
	}
	len = ft_strlen(*dst);
	if (start > len)
		start = len;
	if (!(*dst))
	{
		if (!(*dst = ft_strdup(src)))
			return (0);
	}
	else if (!ft_strstradd_assist(dst, start, src))
	{
		ft_free((void**)dst);
		return (0);
	}
	return (1);
}
