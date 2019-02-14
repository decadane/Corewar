/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 14:09:02 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/14 15:31:21 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	add_process(t_list *procs, t_player *player, t_process *parent)
{
	t_process *new;
	int i;

	new = (t_process*)malloc(sizeof(t_process));
	if (player)
	{
		(new->registry)[0] = -(player->id);
		i = 1;
		while (i < REG_NUMBER)
			(new->registry)[i++] = 0;
	}
	else if (parent)
	{
		i = 0;
		while (i < REG_NUMBER)
			(new->registry)[i] = (parent->registry)[i++];
	}


	new->carry = false;





}

void	init_arena(t_player **players, int num_of_pl, int dump)
{
	t_vm	*arene;
	t_list	*procs;
	int		i;

	arene = (t_vm*)malloc(sizeof(t_vm));
	i = 0;
	while (i < MEM_SIZE)
		arene->map[i++] = 0;
	arene->num_of_players = num_of_pl;
	arene->cycles_passed = 0;
	arene->lives_per_cycle = 0;
	arene->cycles_to_die = CYCLE_TO_DIE;
	arene->num_of_checks = 0;
	arene->dump = (dump >= 0) ? dump : -1;
	arene->players = players;
	i = 0;
	procs = NULL;
	while (players[i])
		add_process(procs, players[i++], 0);

}