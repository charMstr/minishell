/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:14:46 by mli               #+#    #+#             */
/*   Updated: 2020/01/03 20:58:12 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi_ptr(const char *str, int *i)
{
	int signe;
	int result;

	signe = 1;
	result = 0;
	while (str[*i] == '\t' || str[*i] == '\n' || str[*i] == '\v' ||
			str[*i] == '\f' || str[*i] == '\r' || str[*i] == ' ')
		(*i)++;
	if (str[*i] == '+')
		(*i)++;
	else if (str[*i] == '-')
	{
		signe *= -1;
		(*i)++;
	}
	while (str[*i] >= '0' && str[*i] <= '9')
		result = (10 * result) + str[(*i)++] - '0';
	return (result * signe);
}
