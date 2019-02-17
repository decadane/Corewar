/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:51:01 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/17 14:23:38 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_collect	*ft_create_collect(void)
{
	t_collect	*col;

	col = (t_collect*)malloc(sizeof(t_collect));
	ft_bzero(col->bot_name, sizeof(col->bot_name));
	ft_bzero(col->bot_comment, sizeof(col->bot_comment));
	col->bot_size = 0;
	col->bot_code = NULL;
	col->labels = NULL;
	return (col);
}
