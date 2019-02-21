/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 18:21:48 by ffahey            #+#    #+#             */
/*   Updated: 2018/11/27 15:37:31 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned char	n;

	n = (unsigned char)c;
	if (n < 128)
		write(fd, &n, 1);
	else
	{
		n = 192 + (unsigned char)c / 64;
		write(fd, &n, 1);
		n = 128 + (unsigned char)c % 64;
		write(fd, &n, 1);
	}
}
