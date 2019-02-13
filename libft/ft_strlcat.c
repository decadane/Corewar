/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:40:21 by ffahey            #+#    #+#             */
/*   Updated: 2018/11/23 19:17:50 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	res_len;
	size_t	len;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	if (size == 0)
		return (j);
	res_len = i + j;
	if (size < i)
		return (size + j);
	len = size > res_len ? res_len : size - 1;
	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (src[j] && i < len)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (res_len);
}
