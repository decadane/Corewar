/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:15:35 by ffahey            #+#    #+#             */
/*   Updated: 2018/11/20 19:19:51 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t len)
{
	while (len--)
		*((unsigned char*)ptr + len) = (unsigned char)c;
	return (ptr);
}
