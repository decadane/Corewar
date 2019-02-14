/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 18:41:57 by marvin            #+#    #+#             */
/*   Updated: 2019/02/14 18:48:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_find_separator(char *str)
{
	while (*str)
	{
		if (!ft_isalpha(*str) && !ft_isdigit(*str) && *str != '_')
			return (str);
		str++;
	}
	return (NULL);
}
