/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 15:34:56 by mli               #+#    #+#             */
/*   Updated: 2020/05/30 15:39:13 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_ptrswap(void **a, void **b)
{
	void	*c;

	c = *b;
	*b = *a;
	*a = c;
}
