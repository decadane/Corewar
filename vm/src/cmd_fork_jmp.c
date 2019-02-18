/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fork_jmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 03:06:04 by trhogoro          #+#    #+#             */
/*   Updated: 2019/02/18 16:32:47 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	cmd_zjmp(t_vm *arena, t_process *proc)
{
	short	value;

	value = (cmd_get_data(arena->map, proc->pc + 1, 2));
	value %= IDX_MOD;
	if (proc->carry)
		proc->pc = (proc->pc + value) % MEM_SIZE;
}

void	cmd_fork(t_vm *arena, t_process *proc)
{
	int			value;
	t_process	*new_proc;

	value = cmd_get_data(arena->map, proc->pc + 1, 2) % IDX_MOD;
	new_proc = (t_process *)malloc(sizeof(t_process));
	ft_memmove(new_proc, proc, sizeof(t_process));
	new_proc->pc = (new_proc->pc + value) % MEM_SIZE;
	ft_lstadd(&(arena->procs), ft_lstnew(new_proc, sizeof(t_process)));
	free(new_proc);
	arena->num_of_proc += 1;
	proc->pc = (unsigned short)((proc->pc + 3) % MEM_SIZE);
}

void	cmd_lfork(t_vm *arena, t_process *proc)
{
	int			value;
	t_process	*new_proc;

	value = cmd_get_data(arena->map, proc->pc + 1, 2);
	new_proc = (t_process *)malloc(sizeof(t_process));
	ft_memmove(new_proc, proc, sizeof(t_process));
	new_proc->pc = (new_proc->pc + value) % MEM_SIZE;
	ft_lstadd(&(arena->procs), ft_lstnew(new_proc, sizeof(t_process)));
	free(new_proc);
	arena->num_of_proc += 1;
	proc->pc = (unsigned short)((proc->pc + 3) % MEM_SIZE);
}
