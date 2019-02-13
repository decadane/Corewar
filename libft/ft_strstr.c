/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:54:01 by ffahey            #+#    #+#             */
/*   Updated: 2018/11/22 19:11:35 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (needle[0] == 0)
		return ((char*)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		k = i;
		while (haystack[k++] == needle[j++])
		{
			if (needle[j] == 0)
				return ((char*)haystack + i);
		}
		i++;
	}
	return (NULL);
}
