/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 13:55:47 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/12 18:13:53 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note: 1:stdin  2:stderr		do we need to protect fd??
**
** note2: if fd is not valid, then the write goes to stderr (fd = 2)
*/

void	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		write(2, &c, 1);
}
