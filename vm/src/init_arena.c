/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:09:02 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/16 16:44:34 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	add_process(t_list **procs, t_player *player, t_process *parent, int place)
{
	t_list		*res;
	t_process	*new;
	int			i;

	new = (t_process*)malloc(sizeof(t_process));
	i = 0;
	if (player)
	{
		(new->registry)[i++] = -(player->id);
		while (i < REG_NUMBER)
			(new->registry)[i++] = 0;
	}
	else if (parent)
		while (i < REG_NUMBER)
		{
			(new->registry)[i] = (parent->registry)[i];
			i++;
		}
	new->carry = parent ? parent->carry : false;
	new->last_live = parent ? parent->last_live : 0;
	new->where_am_i = parent ? (parent->where_am_i + place) : player->start_point;
	new->cycles_to_act = 0;
	res = (t_list*)malloc(sizeof(t_list));
	res->content = new;
	res->next = *procs;
	procs = &res;
}

t_list *players_go_to_arena(t_vm *arena, t_player **players, int num_of_pl)
{
	t_list			*procs;
	int				i;
	int				id;
	unsigned char	*start;

	id = 1;
	procs = NULL;
	ft_printf("Introducing contestants...\n");
	while (id <= num_of_pl)
	{
		i = 0;
		while ((players[i])->id != id)
			i++;
		start = &((arena->map)[players[i]->start_point]);
		ft_memcpy(start, (players[i])->code, (players[i])->prog_size);
		add_process(&procs, players[i], 0, 0);
		ft_printf("* Player %d, weighting %d bytes, \"%s\" (\"%s\") !\n", id, (players[i])->prog_size, (players[i])->name, (players[i])->comment);
		id++;
	}
	arena->cur_win_id = i;
	arena->cur_win = players[i]->name;
	return (procs);
}

void	init_arena(t_vm *arena, t_player **players, int num_of_pl, int dump)
{
	t_list	*procs;
	int		i;

	i = 0;
	while (i < MEM_SIZE)
		arena->map[i++] = 0;
	arena->num_of_players = num_of_pl;
	arena->num_of_proc = num_of_pl;
	arena->cycles_passed = 0;
	arena->lives_per_cycle = 0;
	arena->cycles_to_die = CYCLE_TO_DIE;
	arena->dump = (dump >= 0) ? dump : -1;
	arena->players = players;
	procs = players_go_to_arena(arena, players, num_of_pl);
	arena->procs = procs;
}
