/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:00:32 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/16 17:20:20 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		announce_the_winner(t_vm *arena, t_player **players)
{
	int i;

	i = 0;
	while (players[i]->id != arena->cur_win_id)
		i++;
	ft_printf("Contestant %d, \"%s\", has won !", players[i]->id , players[i]->name);
}

int			assign_id(t_player	**player, int num)
{
	int i;
	int j;
	int id;

	i = 0;
	id = 1;
	while (player[i])
	{
		j = 0;
		while (player[j])
			if (player[j++]->id == id)
			{
				id++;
				continue ;
			}
		if ((player[i]->id) > num)
			return(error("Error: the number of the player shall be between 1 and ", ft_itoa(num)));
		if (!(player[i]->id))
			player[i]->id = id++;
		player[i]->start_point = (player[i]->id - 1) * MEM_SIZE / num;
		i++;
	}
	return (1);
}

t_player	**welcome_champions(int ac, char **av, int *dump, int *num)
{
	int			id;
	t_player	**res;

	*dump = -1;
	id = 0;
	res = (t_player**)malloc(sizeof(t_player*) * (MAX_PLAYERS + 1));
	while (id < MAX_PLAYERS)
		res[id++] = NULL;
	id = 0;
	while (ac--)
	{
		if (**av == '-' && (!ft_strcmp(*av, "-n") || !ft_strcmp(*av, "-dump")))
		{
			if (!read_opt(av, dump, &id, res))
				return free_players(res) ? NULL : NULL;
			av++;
			ac--;
		}
		else
		{
			if (!read_champion(*av, res, &id, *num))
				return free_players(res) ? NULL : NULL;
			(*num)++;
		}
		av++;
	}
	if (!(assign_id(res, *num)))
		return free_players(res) ? NULL : NULL;
	return (res);
}

static int  print_usage(void)
{
	ft_putendl("Usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...");
	return (0);
}

int         main(int ac, char **av)
{
	t_player	**players;
	t_vm		*arena;
	int			num_of_pl;
	int			dump;

	if (ac == 1)
		return (print_usage());
	num_of_pl = 0;
	if (!(players = welcome_champions(--ac, ++av, &dump, &num_of_pl)))
		return (1);
	if (!num_of_pl && free_players(players))
		return (print_usage());
	arena = (t_vm*)malloc(sizeof(t_vm));
	init_arena(arena, players, num_of_pl, dump);
	start_the_game(arena);
	announce_the_winner(arena, players);
	free(arena);
	return (0);
}
