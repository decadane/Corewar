/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 03:06:17 by trhogoro          #+#    #+#             */
/*   Updated: 2019/02/18 12:11:56 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	cmd_add(t_vm *arena, t_process *proc)
{
	int	reg1;
	int	reg2;
	int	reg3;

	if (((proc->op_arg >> 6) != A_REG) ||
		(((proc->op_arg >> 4) & 0x3) != A_REG) ||
		(((proc->op_arg >> 2) & 0x3) != A_REG))
		return (wrong_argument(proc));
	reg1 = cmd_get_data(arena->map, proc->pc + 2, 1);
	reg2 = cmd_get_data(arena->map, proc->pc + 3, 1);
	reg3 = cmd_get_data(arena->map, proc->pc + 4, 1);
	if ((reg1 <= 0) || (reg1 > REG_NUMBER) || (reg2 <= 0) ||
		(reg2 > REG_NUMBER) || (reg3 <= 0) || (reg3 > REG_NUMBER))
		return (wrong_argument(proc));
	proc->registry[reg3 - 1] =
	proc->registry[reg1 - 1] + proc->registry[reg2 - 1];
	proc->carry = !(proc->registry[reg3 - 1]);
	proc->pc = (unsigned short)((proc->pc + 5) % MEM_SIZE);
}

void	cmd_sub(t_vm *arena, t_process *proc)
{
	int	reg1;
	int	reg2;
	int	reg3;

	if (((proc->op_arg >> 6) != A_REG) ||
		(((proc->op_arg >> 4) & 0x3) != A_REG) ||
		(((proc->op_arg >> 2) & 0x3) != A_REG))
		return (wrong_argument(proc));
	reg1 = cmd_get_data(arena->map, proc->pc + 2, 1);
	reg2 = cmd_get_data(arena->map, proc->pc + 3, 1);
	reg3 = cmd_get_data(arena->map, proc->pc + 4, 1);
	if ((reg1 <= 0) || (reg1 > REG_NUMBER) || (reg2 <= 0) ||
		(reg2 > REG_NUMBER) || (reg3 <= 0) || (reg3 > REG_NUMBER))
		return (wrong_argument(proc));
	proc->registry[reg3 - 1] =
	proc->registry[reg1 - 1] - proc->registry[reg2 - 1];
	proc->carry = !(proc->registry[reg3 - 1]);
	proc->pc = (unsigned short)((proc->pc + 5) % MEM_SIZE);
}
