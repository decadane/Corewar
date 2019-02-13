/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_str_integer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 12:58:25 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/05 17:50:19 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_isdigit_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int			ft_is_str_integer(char *str)
{
	long	nbr;
	char	*check;

	if (!str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	if (ft_isdigit_str(str) == 0)
		return (0);
	while (*str && *str == '0' && *(str + 1))
		str++;
	nbr = (long)ft_atoi(str);
	if (nbr > INT_MAX || nbr < INT_MIN)
		return (0);
	check = ft_itoa(nbr);
	if (ft_strlen(str) != ft_strlen(check))
	{
		free(check);
		return (0);
	}
	free(check);
	return (1);
}
