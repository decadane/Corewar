/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:35:40 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/18 13:46:30 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned short	g_cyc_to_act[16] = {10, 5, 5, 10, 10,
	6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};

void	get_command(t_vm *arena, t_process *proc)
{
	unsigned short	place;

	place = proc->pc;
	if ((arena->map)[place] < 1 || (arena->map)[place] > 16)
	{
		proc->pc = (proc->pc + 1) % MEM_SIZE;
		return ;
	}
	proc->op = (arena->map)[place];
	proc->op_clr = (arena->color_map)[place];
	proc->cycles_to_act = g_cyc_to_act[proc->op - 1];
}

void	new_cycle(t_vm *arena)
{
	t_list		*procs;
	t_process	*cur_proc;

	procs = arena->procs;
	while (procs)
	{
		cur_proc = (t_process*)(procs->content);
		if (!(cur_proc->cycles_to_act))
			get_command(arena, cur_proc);
		else
		{
			cur_proc->cycles_to_act--;
			if (!(cur_proc->cycles_to_act))
				exec_command(arena, cur_proc);
		}
		procs = procs->next;
	}
}

void	kill_dead_procs(t_list **procs, unsigned int rubicone)
{
	t_list			*prev;
	t_list			*next;
	t_list			*cur;
	unsigned int	last_l;

	prev = 0;
	cur = *procs;
	while (cur)
	{
		next = cur->next;
		last_l = ((t_process*)(cur->content))->last_live;
		if (last_l <= rubicone)
		{
			if (prev)
				prev->next = next;
			else
				*procs = next;
			free(cur->content);
			free(cur);
		}
		else
			prev = cur;
		cur = next;
	}
}

int		start_the_game(t_vm *arena)
{
	unsigned int	cycl_count;
	unsigned int	checks;

	checks = 0;
	while (arena->cycles_to_die > 0 && arena->procs && arena->dump)
	{
		arena->lives_per_cycle = 0;
		cycl_count = arena->cycles_to_die + 1;
		while (--cycl_count > 0)
		{
			new_cycle(arena);
			arena->cycles_passed++;
			--(arena->dump);
			if (!arena->dump)
			{
				ft_print_memory(arena->map, arena->color_map, 4096);
				exit (0);
			}
		}
		kill_dead_procs(&(arena->procs), (arena->cycles_passed -
			arena->cycles_to_die));
		if (arena->lives_per_cycle > NBR_LIVE || checks >= MAX_CHECKS)
		{
			arena->cycles_to_die = arena->cycles_to_die < CYCLE_DELTA ? 0 :
				arena->cycles_to_die - CYCLE_DELTA;
			checks = 0;
		}
		else
			checks++;
	}
	return (0);
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
			(color == 1) ? write(1, "\033[31m", 5) : (void)0;
			(color == 2) ? write(1, "\033[32m", 5) : (void)0;
			(color == 3) ? write(1, "\033[33m", 5) : (void)0;
			(color == 4) ? write(1, "\033[34m", 5) : (void)0;
		}
		ft_putchar((*mem >> 4) + ((*mem >> 4) > 9 ? 'A' - 10 : '0'));
		ft_putchar((*mem & 0xf) + ((*mem & 0xf) > 9 ? 'A' - 10 : '0'));
		ft_putchar(' ');
		mem++;
		(!((i + 1) % 64)) ? ft_putendl("") : (void)0;
	}
}