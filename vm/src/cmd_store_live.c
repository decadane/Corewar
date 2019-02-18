/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trhogoro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 02:12:33 by trhogoro          #+#    #+#             */
/*   Updated: 2019/02/18 02:12:36 by trhogoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm/inc/vm.h"

void	wrong_argument(t_process *process)
{
	process->pc = (process->pc + 1) % MEM_SIZE;
}


void	cmd_live(t_vm *arena, t_process *proc)
{
	int	value;

	value = cmd_get_data(arena->map, proc->pc + 1, 4);
	proc->pc += 5;
	if ((-value > 0) && (-value <= arena->num_of_players))
	{
		proc->last_live = arena->cycles_passed;
		arena->cur_win_id = (short)-value;
		arena->lives_per_cycle += 1;
	}
}


void	cmd_st(t_vm *arena, t_process *proc)
{
	int		from;
	int		to;
	short	value;

	if (((proc->op_arg >> 6) != A_REG) || (((proc->op_arg >> 4) & 0x3) == A_DIR)
		|| (!((proc->op_arg >> 4) & 0x3)) || ((proc->op_arg & 0xf)))
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
		0x3) == A_IND) || ((proc->op_arg) & 0x3))
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


void	cmd_aff(t_vm *arena, t_process *proc)
{
	char	value;
	int		reg;

	if (proc->op_arg != 0x40)
		return (wrong_argument(proc));
	reg = cmd_get_data(arena->map, proc->pc + 2, 1);
	if (reg <= 0 || reg > REG_NUMBER)
		return (wrong_argument(proc));
	value = (char)proc->registry[reg - 1];
	if (arena->aff)
		ft_putchar(value);
	proc->pc = (unsigned short)((proc->pc + 3) % MEM_SIZE);
}

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

void	ft_print_memory(unsigned char *mem, unsigned char *colors, size_t size)
{
	int				i;
	unsigned char	color;

	color = 0;
	i = -1;
	while (++i < size)
	{
		if (colors[i] != color)
		{
			color = colors[i];
			(!color) ? write(1, "\033[0m", 4) : (void)0;
			(color == 1) ? write(1, "\033[30m", 5) : (void)0;
			(color == 2) ? write(1, "\033[31m", 5) : (void)0;
			(color == 3) ? write(1, "\033[32m", 5) : (void)0;
			(color == 4) ? write(1, "\033[33m", 5) : (void)0;
			(color == 5) ? write(1, "\033[34m", 5) : (void)0;
		}
		ft_putchar((*mem >> 4) + ((*mem >> 4) > 9 ? 'A' - 10 : '0'));
		ft_putchar((*mem & 0xf) + ((*mem & 0xf) > 9 ? 'A' - 10 : '0'));
		ft_putchar(' ');
		mem++;
		(!((i + 1) % 64)) ? ft_putendl("") : (void)0;
	}
}
