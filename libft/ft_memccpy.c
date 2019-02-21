/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:47:59 by ffahey            #+#    #+#             */
/*   Updated: 2018/11/28 14:45:42 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	if (dst == src)
		return (dst);
	i = -1;
	while (++i < n)
	{
		*((unsigned char*)dst + i) = *((unsigned char*)src + i);
		if (*((unsigned char*)src + i) == (unsigned char)c)
			return (dst + i + 1);
	}
	return (NULL);
}
