/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbytes_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:49:23 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/19 19:05:58 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** note:	on the given fd, this function will print bytes after bytes of the
**			void pointer.
**
** usage:	ex: ft_putbytes_fd(tab, sizeof(tab), sizeof(*tab), 1);
*/

static void	ft_putelem_fd(void *thing, int sizeof_elem, int fd)
{
	char *ptr;

	ptr = (char*)thing;
	if (!thing || sizeof_elem <= 0)
		return ;
	if (sizeof_elem > 1)
		ft_putelem_fd(ptr + 1, --sizeof_elem, fd);
	ft_putbits_fd(*ptr, fd);
}

void		ft_putbytes_fd(void *thing, int sizeof_thing, int sizeof_elem, \
		int fd)
{
	if (!thing || sizeof_thing <= 0 || sizeof_elem <= 0 || fd < 0)
		return ;
	ft_putelem_fd(thing, sizeof_elem, fd);
	if (sizeof_thing != sizeof_elem)
		ft_putstr_fd("--", 1);
	if (sizeof_thing > 1)
		ft_putbytes_fd(thing + sizeof_elem, sizeof_thing - sizeof_elem, \
				sizeof_elem, fd);
}
