/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_store_live.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 03:06:27 by trhogoro          #+#    #+#             */
/*   Updated: 2019/02/18 22:14:20 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	cmd_live(t_vm *arena, t_process *proc)
{
	int	value;
	int	i;

	value = cmd_get_data(arena->map, proc->pc + 1, 4);
	proc->pc += 5;
	proc->last_live = arena->cycles_passed;
	if ((-value > 0) && (-value <= arena->num_of_players))
	{
		arena->cur_win_id = (short)-value;
		arena->lives_per_cycle += 1;
		i = 0;
		while ((arena->players)[i]->id != arena->cur_win_id)
			i++;
		(arena->players)[i]->tot_lives++;
		if (arena->aff)
			ft_printf("A process shows that player %d (%s) is alive\n",
				arena->cur_win_id, (arena->players)[i]->name);
	}
}

void	cmd_st(t_vm *arena, t_process *proc)
{
	int		from;
	int		to;
	short	value;

	if (((proc->op_arg >> 6) != A_REG) || (((proc->op_arg >> 4) & 0x3) == A_DIR)
		|| (!((proc->op_arg >> 4) & 0x3)))
		return (wrong_argument(proc));
	from = cmd_get_data(arena->map, proc->pc + 2, 1);
	if ((from <= 0) || (from > REG_NUMBER))
		return (wrong_argument(proc));
	if (((proc->op_arg >> 4) & 0x3) == A_REG)
	{
		to = cmd_get_data(arena->map, proc->pc + 3, 1);
		if ((to <= 0) || (to > REG_NUMBER))
			return (wrong_argument(proc));
		proc->registry[to - 1] = proc->registry[from - 1];
		proc->pc = (unsigned short)((proc->pc + 4) % MEM_SIZE);
		return ;
	}
	value = ((short)cmd_get_data(arena->map, proc->pc + 3, 2)) % IDX_MOD;
	cmd_set_data(arena->map, (proc->pc + value) % MEM_SIZE,
	(char *)(&(proc->registry[from - 1])), 4);
	cmd_set_color(arena->color_map, (proc->pc + value) % MEM_SIZE,
		proc->op_clr, 4);
	proc->pc = (unsigned short)((proc->pc + 5) % MEM_SIZE);
}

void	cmd_sti(t_vm *arena, t_process *proc)
{
	int	shift;
	int	value;
	int	reg;

	if (((proc->op_arg >> 6) != A_REG) || !((proc->op_arg >> 4) & 0x3)
		|| !((proc->op_arg >> 2) & 0x3) || (((proc->op_arg >> 2) &
		0x3) == A_IND))
		return (wrong_argument(proc));
	shift = 3;
	reg = cmd_get_data(arena->map, proc->pc + 2, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return (wrong_argument(proc));
	value = cmd_get_int(arena, proc, ((proc->op_arg >> 4) & 0x3) == A_DIR ?
		A_DIR2 : ((proc->op_arg >> 4) & 0x3), &shift);
	if (shift == -1)
		return (wrong_argument(proc));
	value = (value + cmd_get_int(arena, proc, ((proc->op_arg >> 2) & 0x3)
		== A_DIR ? A_DIR2 : A_REG, &shift)) % IDX_MOD;
	if (shift == -1)
		return (wrong_argument(proc));
	cmd_set_data(arena->map, (proc->pc + value) % MEM_SIZE,
		(char *)(&(proc->registry[reg - 1])), 4);
	cmd_set_color(arena->color_map, (proc->pc + value) % MEM_SIZE,
		arena->color_map[proc->pc], 4);
	proc->pc = (unsigned short)((proc->pc + shift) % MEM_SIZE);
}
