/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:26:06 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/18 21:32:32 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_error_output(char *str)
{
	ft_putstr(str);
	ft_putstr(" [line ");
	ft_putnbr((int)g_line_number);
	ft_putstr("]\n");
	exit(-1);
}
