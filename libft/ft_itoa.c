/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 13:22:01 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/05 16:00:30 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	long int	num;
	size_t		size;
	char		*res;

	num = n < 0 ? -(long)n : n;
	size = n <= 0 ? 1 : 0;
	while (num && ++size)
		num /= 10;
	if (!(res = ft_strnew(size)))
		return (NULL);
	num = n < 0 ? -(long)n : n;
	if (num == 0)
		*res = '0';
	else
	{
		while (size-- && num)
		{
			res[size] = num % 10 + '0';
			num /= 10;
		}
		size == 0 ? res[size] = '-' : 0;
	}
	return (res);
}
