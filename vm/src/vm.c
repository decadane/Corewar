/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:00:32 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/18 16:14:35 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		announce_the_winner(t_vm *arena, t_player **players)
{
	int i;

	i = 0;
	while (players[i]->id != arena->cur_win_id)
		i++;
	ft_printf("Contestant %d, \"%s\", has won !\n", players[i]->id,
		players[i]->name);
}

int			assign_id(t_player **player, int num)
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
			return (error(ERR_WRONG_NUM, ft_itoa(num)));
		if (!(player[i]->id))
			player[i]->id = id++;
		player[i]->start_point = (player[i]->id - 1) * MEM_SIZE / num;
		i++;
	}
	return (1);
}

t_player	**welcome_champions(int ac, char **av, t_vm *arena)
{
	int			id;
	t_player	**res;

	id = 0;
	res = (t_player**)malloc(sizeof(t_player*) * (MAX_PLAYERS + 1));
	while (id < MAX_PLAYERS)
		res[id++] = NULL;
	id = 0;
	while (ac--)
	{
		if (**av == '-' && (!ft_strcmp(*av, "-n") || !ft_strcmp(*av, "-dump") ||
		!ft_strcmp(*av, "-a") || !ft_strcmp(*av, "-v")))
		{
			if (!read_opt(&av, arena, &id, res))
				return (free_players(res) ? NULL : NULL);
			if (**av != '-')
				ac--;
		}
		else if (!read_champion(*av, res, &id, arena))
			return (free_players(res) ? NULL : NULL);
		av++;
	}
	if (!(assign_id(res, arena->num_of_players)))
		return (free_players(res) ? NULL : NULL);
	return (res);
}

static int	print_usage(void)
{
	ft_putstr("Usage: ./corewar ");
	ft_putendl(USAGE);
	return (0);
}

int			main(int ac, char **av)
{
	t_player	**players;
	t_vm		*arena;

	if (ac == 1)
		return (print_usage());
	arena = (t_vm*)malloc(sizeof(t_vm));
	arena->aff = 0;
	arena->vis = 0;
	arena->dump = -1;
	arena->num_of_players = 0;
	if (!(players = welcome_champions(--ac, ++av, arena)))
		return (1);
	if (!arena->num_of_players && free_players(players))
		return (print_usage());
	init_arena(arena, players);
	start_the_game(arena);
	announce_the_winner(arena, players);
	if (arena->vis)
		ft_print_memory(arena->map, arena->color_map, 4096);
	free_arena(arena);
	return (0);
}
