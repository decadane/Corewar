/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 21:13:25 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/13 22:04:16 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		read_opt(char **av, int *dump, int *id)
{
	av++;
	if (*(*av + 1) == 'n')
	{
		*id = ft_atoi(*av);
		if (id <= 0 || id > MAX_PLAYERS || **av < '0' || **av > '9')
			return (error("Invalid champion's number!", 0));
	}
	else
	{
		*dump = ft_atoi(*av);
		if (*dump < 0 || **av < '0' || **av > '9')
			return (error("Invalid dump!", 0));
	}
	return (1);
}

int		read_champion(char *av, t_player **player, int *id)
{
	int		fd;
	int		i;
	int		size;
	char	magic[4];

	if ((fd = open(*av, O_RDONLY)) == -1)
		return (error("Can't read source file ", *av));
	read(fd, magic, 4);
	if ((int)magic != COREWAR_EXEC_MAGIC)
		return(error2("Error: File ", *av, " has an invalid header"));
	i = 0;
	while (player[i])
		i++;
	player[i] = (t_player*)malloc(sizeof(t_player));
	read(fd, player[i]->name, 128);
	read(fd, magic, 4);
	if ((int)magic != 0)
		return(error2("Error: File ", *av, " has an invalid header"));
	read(fd, player[i]->prog_size, 4);
	read(fd, player[i]->comment, 2048);
	read(fd, magic, 4);
	if ((int)magic != 0)
		return(error2("Error: File ", *av, " has an invalid header"));
	size = 0;
	while (read(fd, (player[i]->code)[size], 1) && size < CHAMP_MAX_SIZE)
		size++;
	if (size >= CHAMP_MAX_SIZE || size != player[i]->prog_size)
		return (error2("Error: file ", av, " is of wrong size"));
	if (*id && (player[i]->id = *id))
		*id = 0;
	return (1);
}
