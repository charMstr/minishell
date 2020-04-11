/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:06:58 by mli               #+#    #+#             */
/*   Updated: 2020/04/12 00:08:07 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2, int to_free)
{
	char *res;

	res = ft_strjoin(s1, s2);
	if (to_free & 1)
		ft_free((void **)&s1);
	if (to_free & 2)
		ft_free((void **)&s2);
	return (res);
}
