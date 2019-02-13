/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:55:47 by ffahey            #+#    #+#             */
/*   Updated: 2018/11/21 20:51:21 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		res;

	i = -1;
	while (++i < n)
	{
		if (*((unsigned char*)s1 + i) != *((unsigned char*)s2 + i))
		{
			res = (int)(*((unsigned char*)s1 + i) - *((unsigned char*)s2 + i));
			return (res);
		}
	}
	return (0);
}
