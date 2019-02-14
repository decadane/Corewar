/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:09:02 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/14 17:02:52 by kcarrot          ###   ########.fr       */
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
	res = (t_list*)malloc(sizeof(t_list));
	res->content = new;
	res->next = *procs;
	procs = &res;
}

void	unload_code(unsigned char map[MEM_SIZE], t_player *player)
{
	int i;

	i = player->start_point;
	ft_memcpy(&(map[i]), player->code, player->prog_size);
}

void	init_arena(t_vm *arena, t_player **players, int num_of_pl, int dump)
{
	t_list	*procs;
	int		i;
	int		id;

	i = 0;
	while (i < MEM_SIZE)
		arena->map[i++] = 0;
	arena->num_of_players = num_of_pl;
	arena->cycles_passed = 0;
	arena->lives_per_cycle = 0;
	arena->cycles_to_die = CYCLE_TO_DIE;
	arena->num_of_checks = 0;
	arena->dump = (dump >= 0) ? dump : -1;
	arena->players = players;
	id = 1;
	procs = NULL;
	while (id <= num_of_pl)
	{
		i = 0;
		while (players[i]->id != id)
			i++;
		unload_code(arena->map, players[i]);
		add_process(&procs, players[i], 0, 0);
		id++;
	}
	arena->processes = procs;
}
