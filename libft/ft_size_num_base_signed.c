/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_num_base_signed.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 03:09:28 by charmstr          #+#    #+#             */
/*   Updated: 2019/12/09 03:13:20 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** note:	this function will predict the size of a number, given its base,
**			its type signed or unsigned, and if you want the absolute size or
**			not.
**
** note2:	if the base is 10, and the numebr is negative and the option
**			absolute is zero, then we add extra space for the minus sign.
*/

int	ft_size_num_base_signed(void *num, int base, int signed_, int absolute)
{
	int				i;
	unsigned int	u_num;
	int				s_num;

	u_num = *(unsigned int*)num;
	s_num = *(int*)num;
	i = 0;
	if (!s_num || !u_num)
		return (1);
	if (signed_)
	{
		if (base == 10 && s_num < 0 && !absolute)
			i++;
		while (s_num && ++i)
			s_num = s_num / base;
		return (i);
	}
	else
	{
		if (base == 10 && u_num < 0 && !absolute)
			i++;
		while (u_num && ++i)
			u_num = u_num / base;
		return (i);
	}
}
