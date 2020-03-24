/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbits_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:41:17 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/13 18:04:13 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** this function will display each bits in a char in this format "[0100 0001]"
*/

void	ft_putbits_fd(char c, int fd)
{
	char i;

	i = 8;
	ft_putchar_fd('[', fd);
	while (--i >= 0)
	{
		ft_putchar_fd(((c & (1 << i)) >> i) + 48, fd);
		if (i == 4)
			ft_putchar_fd(' ', fd);
	}
	ft_putchar_fd(']', fd);
}
