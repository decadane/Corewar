/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:00:36 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/01 13:58:49 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long int	res;
	long int	check;
	char		sign;

	sign = 1;
	res = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		check = res;
		res = res * 10 + (*str - 48);
		if (res < check)
			return (sign < 0 ? 0 : -1);
		str++;
	}
	return ((int)(res * sign));
}
