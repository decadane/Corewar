/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_filename.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:20:41 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/19 13:39:19 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_check_filename(char *str)
{
	char	*dot;
	char	*filename;

	filename = NULL;
	if (str)
	{
		if (!(dot = ft_strrchr(str, '.')) || ft_strcmp(dot, ".s"))
		{
			ft_putstr("Invalid filename: ");
			ft_putendl(str);
			exit(0);
		}
		filename = ft_strsub(str, 0, dot - str);
	}
	return (filename);
}
