/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funclions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 17:03:15 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/14 18:47:13 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_del_label(void *ptr, size_t size)
{
	free(((t_label*)ptr)->name);
	ft_bzero(ptr, size);
	free(ptr);
}

void	ft_free_collect(t_collect *col)
{
	ft_bzero(col->bot_name, sizeof(col->bot_name));
	ft_bzero(col->bot_comment, sizeof(col->bot_comment));
	col->bot_size = 0;
	free(col->bot_code);
	ft_lstdel(&col->labels, ft_del_label);
	free(col);
}
