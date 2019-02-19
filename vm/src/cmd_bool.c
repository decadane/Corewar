/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_bool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 03:05:58 by trhogoro          #+#    #+#             */
/*   Updated: 2019/02/18 12:11:33 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	cmd_and(t_vm *arena, t_process *proc)
{
	int	value1;
	int	value2;
	int	reg;
	int	shift;

	if (!(proc->op_arg >> 6) ||
		!((proc->op_arg >> 4) & 0x3) ||
		(((proc->op_arg >> 2) & 0x3) != A_REG))
		return (wrong_argument(proc));
	shift = 2;
	value1 = cmd_get_int(arena, proc, (proc->op_arg >> 6), &shift);
	if (shift == ERR_FLAG)
		return (wrong_argument(proc));
	value2 = cmd_get_int(arena, proc, (proc->op_arg >> 4) & 0x3, &shift);
	if (shift == ERR_FLAG)
		return (wrong_argument(proc));
	reg = cmd_get_data(arena->map, (proc->pc + shift) % MEM_SIZE, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return (wrong_argument(proc));
	proc->registry[reg - 1] = value1 & value2;
	proc->carry = (!(proc->registry[reg - 1]));
	proc->pc = (unsigned short)((proc->pc + shift + 1) % MEM_SIZE);
}

void	cmd_or(t_vm *arena, t_process *proc)
{
	int	value1;
	int	value2;
	int	reg;
	int	shift;

	if (!(proc->op_arg >> 6) ||
		!((proc->op_arg >> 4) & 0x3) ||
		(((proc->op_arg >> 2) & 0x3) != A_REG))
		return (wrong_argument(proc));
	shift = 2;
	value1 = cmd_get_int(arena, proc, (proc->op_arg >> 6), &shift);
	if (shift == ERR_FLAG)
		return (wrong_argument(proc));
	value2 = cmd_get_int(arena, proc, (proc->op_arg >> 4) & 0x3, &shift);
	if (shift == ERR_FLAG)
		return (wrong_argument(proc));
	reg = cmd_get_data(arena->map, (proc->pc + shift) % MEM_SIZE, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return (wrong_argument(proc));
	proc->registry[reg - 1] = value1 | value2;
	proc->carry = !(proc->registry[reg - 1]);
	proc->pc = (unsigned short)((proc->pc + shift + 1) % MEM_SIZE);
}

void	cmd_xor(t_vm *arena, t_process *proc)
{
	int	value1;
	int	value2;
	int	reg;
	int	shift;

	if (!(proc->op_arg >> 6) ||
		!((proc->op_arg >> 4) & 0x3) ||
		(((proc->op_arg >> 2) & 0x3) != A_REG))
		return (wrong_argument(proc));
	shift = 2;
	value1 = cmd_get_int(arena, proc, (proc->op_arg >> 6), &shift);
	if (shift == ERR_FLAG)
		return (wrong_argument(proc));
	value2 = cmd_get_int(arena, proc, (proc->op_arg >> 4) & 0x3, &shift);
	if (shift == ERR_FLAG)
		return (wrong_argument(proc));
	reg = cmd_get_data(arena->map, (proc->pc + shift) % MEM_SIZE, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return (wrong_argument(proc));
	proc->registry[reg - 1] = value1 ^ value2;
	proc->carry = !(proc->registry[reg - 1]);
	proc->pc = (unsigned short)((proc->pc + shift + 1) % MEM_SIZE);
}
