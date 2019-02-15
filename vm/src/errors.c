/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 21:13:00 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/15 16:26:54 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		error(char *str, char *param)
{
	ft_putstr_fd(str, 2);
	if (param)
		ft_putstr_fd(param, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int		error2(char *str, char *param, char *str2)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(param, 2);
	ft_putchar_fd(' ', 2);
	ft_putendl_fd(str2, 2);
	return (0);
}
