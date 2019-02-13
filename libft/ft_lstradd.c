/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstradd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trhogoro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 20:03:37 by trhogoro          #+#    #+#             */
/*   Updated: 2018/11/20 07:56:57 by trhogoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstradd(t_list **alst, t_list *new1)
{
	t_list *temp;

	if (!alst)
		return ;
	temp = *alst;
	if (temp)
	{
		while ((temp)->next)
			(temp) = (temp)->next;
		(temp)->next = new1;
	}
	else
		*alst = new1;
}
