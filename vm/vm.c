/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:00:32 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/14 14:03:48 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_player	*welcome_champions(int ac, char **av, int *dump, int *num)
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
			if (!read_opt(av, dump, &id) && free_players(res))
				return(0);
		else
		{
			if (!read_champion(*av, res, &id, *num) && free_players(res))
				return (0);
			(*num)++;
		}
		av++;
	}
	return (res);
}

static int  print_usage(void)
{
	ft_putendl("Usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...");
	return (0);
}

int         main(int ac, char **av)
{
	t_player	*players;
	int			num_of_pl;
	int			dump;

	if (ac == 1)
		return (print_usage());
	num_of_pl = 0;
	if (!(players = welcome_champions(--ac, ++av, &dump, &num_of_pl)))
		return (1);
	if (!num_of_pl && free_players(players))
		return (print_usage());
	


}
