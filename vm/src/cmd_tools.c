/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 03:06:34 by trhogoro          #+#    #+#             */
/*   Updated: 2019/02/18 12:12:03 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	exec_command(t_vm *arena, t_process *proc)
{
	if ((proc->op != 1) &&
		(proc->op != 9) &&
		(proc->op != 12) &&
		(proc->op != 15))
		proc->op_arg = cmd_get_data(arena->map,
			(proc->pc + 1) % MEM_SIZE, 1);
	if ((proc->op <= 16) && (proc->op >= 0))
		arena->f_com[proc->op - 1](arena, proc);
}

void	init_commands_array(t_vm *arena)
{
	arena->f_com[0] = cmd_live;
	arena->f_com[1] = cmd_ld;
	arena->f_com[2] = cmd_st;
	arena->f_com[3] = cmd_add;
	arena->f_com[4] = cmd_sub;
	arena->f_com[5] = cmd_and;
	arena->f_com[6] = cmd_or;
	arena->f_com[7] = cmd_xor;
	arena->f_com[8] = cmd_zjmp;
	arena->f_com[9] = cmd_ldi;
	arena->f_com[10] = cmd_sti;
	arena->f_com[11] = cmd_fork;
	arena->f_com[12] = cmd_lld;
	arena->f_com[13] = cmd_lldi;
	arena->f_com[14] = cmd_lfork;
	arena->f_com[15] = cmd_aff;
}

void	wrong_argument(t_process *process)
{
	process->pc = (process->pc + 1) % MEM_SIZE;
}
