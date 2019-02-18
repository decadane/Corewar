/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 03:07:57 by trhogoro          #+#    #+#             */
/*   Updated: 2019/02/18 12:11:48 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	cmd_ld(t_vm *arena, t_process *proc)
{
	int		value;
	int		reg;
	char	is_dir;

	if (((proc->op_arg >> 6) == A_DIR) && (((proc->op_arg >> 4) &
		0x3) == A_REG) && (!(proc->op_arg & 0xf)))
		is_dir = 1;
	else if (((proc->op_arg >> 6) == A_IND) && (((proc->op_arg >> 4)
		& 0x3) == A_REG) && (!(proc->op_arg & 0xf)))
		is_dir = 0;
	else
		return (wrong_argument(proc));
	value = cmd_get_data(arena->map, proc->pc + ((is_dir) ? 2 :
	(cmd_get_data(arena->map, proc->pc + 2, 2) % IDX_MOD)), 4);
	reg = cmd_get_data(arena->map, proc->pc + 4 + is_dir * 2, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return (wrong_argument(proc));
	proc->registry[reg - 1] = value;
	proc->pc = (unsigned short)((proc->pc + 5 + is_dir * 2) % MEM_SIZE);
	proc->carry = !value;
}

void	cmd_ldi(t_vm *arena, t_process *proc)
{
	int		shift;
	short	value;
	int		reg;

	if (!(proc->op_arg >> 6) || !((proc->op_arg >> 4) & 0x3) ||
		(((proc->op_arg >> 4) & 0x3) == A_IND) ||
		(((proc->op_arg >> 2) & 0x3) != A_REG) ||
		((proc->op_arg) & 0x3))
		return (wrong_argument(proc));
	shift = 2;
	value = (short)(cmd_get_int(arena, proc, (proc->op_arg >> 6) == A_DIR
		? A_DIR2 : (proc->op_arg >> 6), &shift));
	if (shift == -1)
		return (wrong_argument(proc));
	value += (short)(cmd_get_int(arena, proc, ((proc->op_arg >> 4) & 0x3)
		== A_DIR ? A_DIR2 : A_REG, &shift));
	if (shift == -1)
		return (wrong_argument(proc));
	reg = cmd_get_data(arena->map, (proc->pc + shift) % MEM_SIZE, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return (wrong_argument(proc));
	proc->registry[reg - 1] = cmd_get_data(arena->map, (proc->pc +
		(value % IDX_MOD)) % MEM_SIZE, 4);
	proc->pc = (unsigned short)((proc->pc + shift + 1) % MEM_SIZE);
}

void	cmd_lld(t_vm *arena, t_process *proc)
{
	int		value;
	int		reg;
	char	is_dir;

	if (((proc->op_arg >> 6) == A_DIR) && (((proc->op_arg >> 4) &
		0x3) == A_REG) && (!(proc->op_arg & 0xf)))
		is_dir = 1;
	else if (((proc->op_arg >> 6) == A_IND) && (((proc->op_arg >> 4) &
		0x3) == A_REG) && (!(proc->op_arg & 0xf)))
		is_dir = 0;
	else
		return (wrong_argument(proc));
	value = cmd_get_data(arena->map, proc->pc + ((is_dir) ? 2 :
	(cmd_get_data(arena->map, proc->pc + 2, 2))), 4);
	reg = cmd_get_data(arena->map, proc->pc + 4 + is_dir * 2, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return (wrong_argument(proc));
	proc->registry[reg - 1] = value;
	proc->pc = (unsigned short)((proc->pc + 5 + is_dir * 2) % MEM_SIZE);
	proc->carry = !value;
}

void	cmd_lldi(t_vm *arena, t_process *proc)
{
	int		shift;
	short	value;
	int		reg;

	if (!(proc->op_arg >> 6) || !((proc->op_arg >> 4) & 0x3) ||
		(((proc->op_arg >> 4) & 0x3) == A_IND) ||
		(((proc->op_arg >> 2) & 0x3) != A_REG) ||
		((proc->op_arg) & 0x3))
		return (wrong_argument(proc));
	shift = 2;
	value = (short)(cmd_get_int(arena, proc, (proc->op_arg >> 6) == A_DIR ?
		A_DIR2 : (proc->op_arg >> 6), &shift));
	if (shift == -1)
		return (wrong_argument(proc));
	value += (short)(cmd_get_int(arena, proc,
		((proc->op_arg >> 4) & 0x3) == A_DIR ? A_DIR2 : A_REG, &shift));
	if (shift == -1)
		return (wrong_argument(proc));
	reg = cmd_get_data(arena->map, (proc->pc + shift) % MEM_SIZE, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return (wrong_argument(proc));
	proc->registry[reg - 1] = cmd_get_data(arena->map,
		(proc->pc + value) % MEM_SIZE, 4);
	proc->pc = (unsigned short)((proc->pc + shift + 1) % MEM_SIZE);
}
