/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:27:24 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/18 18:28:02 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

//DELETE THIS
void		print_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	printf("Label: %s|\n", cmd->label);
	printf("Opcode: %d\n", cmd->opcode);
	printf("Codage: %x\n", cmd->codage);
	printf("Arg1: %s|\n", cmd->args[0]);
	printf("Arg2: %s|\n", cmd->args[1]);
	printf("Arg3: %s|\n", cmd->args[2]);
	printf("Parg1: %d|\n", cmd->pargs[0]);
	printf("Parg2: %d|\n", cmd->pargs[1]);
	printf("Parg3: %d|\n", cmd->pargs[2]);
	printf("Size: %d\n", cmd->size);
}

void		print_cmd_list(t_list *lst)
{
	while (lst)
	{
		print_cmd((t_cmd*)lst->content);
		lst = lst->next;
	}
}

void		print_lbl(t_label *lbl)
{
	if (!lbl)
		return ;
	printf("Label: %s|\n", lbl->name);
	printf("Offset: %d\n", lbl->offset);
}

void		print_lbl_list(t_list *lst)
{
	while (lst)
	{
		print_lbl((t_label*)lst->content);
		lst = lst->next;
	}
}
