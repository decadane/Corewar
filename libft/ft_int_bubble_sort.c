/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_bubble_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:47:29 by ffahey            #+#    #+#             */
/*   Updated: 2019/01/26 12:33:09 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_arr_cpy(int *dst, int *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
}

int			*ft_int_bubble_sort(int *arr, size_t size)
{
	int			*sort_arr;
	size_t		i;
	size_t		j;

	sort_arr = NULL;
	if (arr && size > 0)
	{
		if ((sort_arr = (int*)malloc(sizeof(int) * size)) == NULL)
			exit(1);
		ft_arr_cpy(sort_arr, arr, size);
		i = 0;
		while (i < size - 1)
		{
			j = i + 1;
			while (j < size)
			{
				if (sort_arr[j] < sort_arr[i])
					ft_int_swap(sort_arr + i, sort_arr + j);
				j++;
			}
			i++;
		}
	}
	return (sort_arr);
}
