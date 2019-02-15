/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_filename.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:20:41 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/14 16:34:34 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_check_filename(char *str)
{
	char	*dot;

	if (str)
	{
		if (!(dot = ft_strrchr(str, '.')) || ft_strcmp(dot, ".s"))
			ft_error_output("Wrong file");
	}
	return (str);
}
