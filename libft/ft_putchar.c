/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 17:39:02 by ffahey            #+#    #+#             */
/*   Updated: 2018/11/27 15:37:16 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	unsigned char	n;

	n = (unsigned char)c;
	if (n < 128)
		write(1, &n, 1);
	else
	{
		n = 192 + (unsigned char)c / 64;
		write(1, &n, 1);
		n = 128 + (unsigned char)c % 64;
		write(1, &n, 1);
	}
}
