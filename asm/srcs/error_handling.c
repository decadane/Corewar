/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:46:30 by marvin            #+#    #+#             */
/*   Updated: 2019/02/14 16:02:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_return_error(int error_code)
{
	if (error_code == 1)
		ft_putstr_fd("usage: ./asm champion_file.s\n", 1);
	if (error_code == 2)
		ft_putstr_fd("Input error: file not found\n", 2);
	return (error_code);
}
