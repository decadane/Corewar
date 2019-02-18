/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:09:02 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/18 14:52:52 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		add_process(t_list **procs, t_player *player, t_process *parent,
			int place)
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
		while (i++ < REG_NUMBER)
			(new->registry)[i - 1] = (parent->registry)[i - 1];
	new->carry = parent ? parent->carry : false;
	new->last_live = parent ? parent->last_live : 0;
	new->pc = parent ? (parent->pc + place) : player->start_point;
	new->cycles_to_act = 0;
	res = (t_list*)malloc(sizeof(t_list));
	res->content = new;
	res->content_size = sizeof(t_process);
	res->next = 0x0;
	ft_lstradd(procs, res);
}

t_list		*players_go_to_arena(t_vm *arena, t_player **players, int num_of_pl)
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
		ft_printf("* Player %d, weighting %d bytes, \"%s\" (\"%s\") !\n", id,
			(players[i])->prog_size, (players[i])->name, (players[i])->comment);
		id++;
	}
	arena->cur_win_id = i + 1;
	return (procs);
}

void		init_arena(t_vm *arena, t_player **players)
{
	t_list			*procs;
	int				num_of_pl;
	int				i;
	unsigned int	j;

	ft_memset(arena->map, 0, MEM_SIZE);
	ft_memset(arena->color_map, 0, MEM_SIZE);
	num_of_pl = arena->num_of_players;
	arena->num_of_proc = num_of_pl;
	arena->cycles_passed = 0;
	arena->lives_per_cycle = 0;
	arena->cycles_to_die = CYCLE_TO_DIE;
	arena->players = players;
	procs = players_go_to_arena(arena, players, num_of_pl);
	arena->procs = procs;
	while (--num_of_pl >= 0)
	{
		i = (players[num_of_pl])->start_point;
		j = 0;
		while (j++ < (players[num_of_pl])->prog_size)
			arena->color_map[i++] = (players[num_of_pl])->id;
	}
	init_commands_array(arena);
}
