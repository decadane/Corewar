/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:06:35 by ffahey            #+#    #+#             */
/*   Updated: 2019/01/26 12:32:25 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_int_arr(int *arr, size_t size)
{
	size_t	i;

	if (arr)
	{
		i = 0;
		while (i < size)
		{
			ft_putnbr(arr[i++]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
