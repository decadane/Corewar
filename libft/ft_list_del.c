/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:45:40 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/13 18:49:22 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_del(t_list *prev, t_list *cur)
{
	t_list *next;

	next = cur->next;
	prev->next = next;
	free(cur->content);
	free(cur);
	cur = NULL;
}
