/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 15:27:03 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/10 16:51:06 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n < -9)
			ft_putnbr_fd(-(n / 10), fd);
	}
	else if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	(n > 0) ? ft_putchar_fd(n % 10 + '0', fd) \
		: ft_putchar_fd(-(n % 10) + '0', fd);
}
