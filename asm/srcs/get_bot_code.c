/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bot_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 18:46:20 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/18 17:17:16 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_get_bot_code(int fd, t_collect *col)
{
	t_list	*lst;
	t_list	*labels;
	int		code_start_line;

	labels = NULL;
	code_start_line = g_line_number;
	lst = ft_parse_exec_code(fd);
	g_line_number = code_start_line;
	lst = ft_process_lst(lst, labels, 1);
	labels = ft_collect_labels(lst);
	g_line_number = code_start_line;
	lst = ft_process_lst(lst, labels, 2);
	ft_process_to_bytecode(lst, col);
	ft_lstdel(&lst, ft_cmd_destroyer);
	ft_lstdel(&labels, ft_lbl_destroyer);
}
