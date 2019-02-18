/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_labels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:12:37 by marvin            #+#    #+#             */
/*   Updated: 2019/02/18 14:04:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_list		*ft_collect_labels(t_list *lst)
{
	t_label		*lbl;
	t_list		*lbl_lst;
	t_list		*lbl_tmp;
	unsigned	offset;

	offset = 0;
	lbl_lst = NULL;
	while (lst)
	{
		if (((t_cmd*)lst->content)->label)
		{
			lbl = ft_lbl_creator();
			lbl->name = ((t_cmd*)lst->content)->label;
			lbl->offset = offset;
			lbl_tmp = ft_lstnew(lbl, sizeof(t_label));
			ft_lstradd(&lbl_lst, lbl_tmp);
			free(lbl);
		}
		offset += ((t_cmd*)lst->content)->size;
		lst = lst->next;
	}
	return (lbl_lst);
}
