/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 21:13:00 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/14 15:44:20 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		error(char *str, char *param)
{
	ft_putstr(str);
	if (param)
		ft_putstr(param);
	ft_putchar('\n');
	return (0);
}

int		error2(char *str, char *param, char *str2)
{
	ft_putstr(str);
	ft_putstr(param);
	ft_putchar(' ');
	ft_putendl(str2);
	return (0);
}
