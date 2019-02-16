/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:31:06 by marvin            #+#    #+#             */
/*   Updated: 2019/02/16 13:18:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_init_cmd_array(char *arr[17])
{
	arr[0] = "live";
	arr[1] = "ld";
	arr[2] = "st";
	arr[3] = "add";
	arr[4] = "sub";
	arr[5] = "and";
	arr[6] = "or";
	arr[7] = "xor";
	arr[8] = "zjmp";
	arr[9] = "ldi";
	arr[10] = "sti";
	arr[11] = "fork";
	arr[12] = "lld";
	arr[13] = "lldi";
	arr[14] = "lfork";
	arr[15] = "aff";
	arr[16] = NULL;
}
//DELETE THIS

void	print_cmd(t_cmd *cmd)
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
	printf("Num: %d\n", cmd->num);
}

void	print_cmd_list(t_list *lst)
{
	while (lst)
	{
		print_cmd((t_cmd*)lst->content);
		lst = lst->next;
	}
}
