/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:00:32 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/13 21:25:21 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_player	*welcome_champions(int ac, char **av, int *dump)
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
			if (!read_opt(av, dump, &id))
				return(0);
		else
		{
			if (!read_champion(*av, res, &id) && free_players(res))
				return (0);

		}
		av++;
	}


}

static int  print_usage(void)
{
	ft_putendl("Usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...");
	return (0);
}

int         main(int ac, char **av)
{
	t_player	*players;
	int			dump;

	if (ac == 1)
		return (print_usage());
	if (!(players = welcome_champions(--ac, ++av, &dump)))
		return (1);
	


}
