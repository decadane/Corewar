/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 11:35:47 by ffahey            #+#    #+#             */
/*   Updated: 2019/01/23 11:58:30 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*str;

	if (s1 == NULL)
		return (NULL);
	size = ft_strlen(s1);
	str = (char*)malloc(size * sizeof(char) + 1);
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	return (str);
}
