/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 14:19:17 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/10 15:26:35 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note: usefull for error messages: 1 --> stdout		2 --> stderr
**
** note2: if fd was not valid, message is redirected to stderr
*/

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (write(fd, s, ft_strlen(s)) == -1)
		write(2, s, ft_strlen(s));
}
