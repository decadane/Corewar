/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 10:58:46 by ffahey            #+#    #+#             */
/*   Updated: 2018/11/25 15:40:14 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char		*ft_strtrim(const char *s)
{
	char	*str;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	while (is_whitespace(s[size - 1]))
		size--;
	while (is_whitespace(*s) && size > 0)
	{
		s++;
		size--;
	}
	if (!(str = ft_strnew(size)))
		return (NULL);
	ft_memcpy(str, s, size);
	return (str);
}
