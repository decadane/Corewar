/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:28:18 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/02 12:31:46 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_getsize(const char *s, char c)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			size++;
		i++;
	}
	return (size);
}

void			ft_free_tab(char ***tab)
{
	size_t	size;

	size = 0;
	while ((*tab)[size] != NULL)
		size++;
	while (size--)
		free((*tab)[size]);
	free(*tab);
	*tab = NULL;
}

static char		**ft_filltab(char **tab, const char *s, char c, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (i < size)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (!(tab[i] = ft_strsub(s, 0, len)))
		{
			while (i)
				free(tab[--i]);
			return (NULL);
		}
		s += len;
		i++;
	}
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	size;

	if (s == NULL)
		return (NULL);
	size = ft_getsize(s, c);
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (size + 1))))
		return (NULL);
	if (!(tab = ft_filltab(tab, s, c, size)))
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}
