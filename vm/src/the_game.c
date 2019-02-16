/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:35:40 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/16 16:44:40 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_command(t_vm *arena, t_process* proc)
{
	unsigned short	place;

	place = proc->where_am_i;
	if ((arena->map)[place] < 1 || (arena->map)[place] > 16)
	{
		proc->where_am_i++;
		return ;
	}


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
			get_command(arena, cur_proc); // Устанавливается cur_op, cur_op_args и cycles_to_act
		else
		{
			cur_proc->cycles_to_act--;
			if (!(cur_proc->cycles_to_act))
				exec_command(arena, cur_proc); // Выполняется cur-op, каретка сдвигается на next_set (меняется where_am_i)
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

int     start_the_game(t_vm *arena)
{
	unsigned int	cycl_count;
	unsigned int	checks;

	checks = 0;
	while (arena->cycles_to_die > 0 && arena->procs)
	{
		arena->lives_per_cycle = 0;
		cycl_count = arena->cycles_to_die;
		while (cycl_count > 0)
		{
			new_cycle(arena);
			arena->cycles_passed++;
			cycl_count--;
		}
		kill_dead_procs(&(arena->procs), (arena->cycles_passed - arena->cycles_to_die));
		if (arena->lives_per_cycle > NBR_LIVE || checks >= MAX_CHECKS)
		{
			arena->cycles_to_die = arena->cycles_to_die < CYCLE_DELTA ? 0 : arena->cycles_to_die - CYCLE_DELTA;
			checks = 0;
		}
		else
			checks++;
	}
	ft_printf("Contestant %d, \"%s\", has won !", arena->cur_win_id, arena->cur_win);
	return (0);
}
