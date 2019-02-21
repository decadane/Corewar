/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 19:55:18 by ffahey            #+#    #+#             */
/*   Updated: 2018/11/22 20:30:30 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (needle[0] == 0)
		return ((char*)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		k = i;
		while (haystack[k] == needle[j] && k < len)
		{
			k++;
			j++;
			if (needle[j] == 0)
				return ((char*)haystack + i);
		}
		i++;
	}
	return (NULL);
}
