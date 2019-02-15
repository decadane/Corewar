/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 21:13:25 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/15 15:40:51 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	change_endian(void *a, int size)
{
	int				i;
	unsigned long	b;
	unsigned char	*src;
	unsigned char	*dest;

	b = 0;
	i = 0;
	src = (unsigned char*)a + size - 1;
	dest = (unsigned char*)&b;
	while (i < size)
	{
		*(dest + i) = *(src - i);
		i++;
	}
	src = (unsigned char*)a;
	while (size--)
		src[size] = dest[size];
}

int		read_opt(char **av, int *dump, int *id, t_player **player)
{
	if (*(*av + 1) == 'n')
	{
		av++;
		*id = ft_atoi(*av);
		if (*id <= 0 || *id > MAX_PLAYERS || **av < '0' || **av > '9')
			return (error("Error: invalid champion's number", 0));
		while (*player)
		{
			if ((*player)->id == *id)
				return (error("Error: all champions shall have different numbers", 0));
			player++;
		}
	}
	else
	{
		av++;
		*dump = ft_atoi(*av);
		if (*dump < 0 || **av < '0' || **av > '9')
			return (error("Error: invalid dump", 0));
	}
	return (1);
}

int		read_champion_header(char *av, t_player **player, int fd)
{
	unsigned int	magic;
	t_player		*new_pl;

	read(fd, &magic, 4);
	if (magic != MAGIC)
		return(error2("Error: File ", av, " has an invalid header"));
	new_pl = (t_player*)malloc(sizeof(t_player));
	read(fd, new_pl->name, PROG_NAME_LENGTH);
	read(fd, &magic, 4);
	if (magic != 0)
		return(error2("Error: File ", av, " has an invalid header"));
	read(fd, &(new_pl->prog_size), 4);
	change_endian(&(new_pl->prog_size), 4);
	read(fd, new_pl->comment, COMMENT_LENGTH);
	read(fd, &magic, 4);
	if (magic != 0)
		return(error2("Error: File ", av, " has an invalid header"));
	*player = new_pl;
	return (1);
}

int		read_champion(char *av, t_player **player, int *id, int num)
{
	int				fd;
	int				i;
	unsigned int	size;

	if (num >= MAX_PLAYERS)
		return (error("Error: too many champions", 0));
	i = 0;
	while (av[i])
		i++;
	if (ft_strcmp(av + i - 4, ".cor"))
		return (error("Error: the source files shall have .cor extension", 0));
	if ((fd = open(av, O_RDONLY)) == -1)
		return (error("Error: can't read source file ", av));
	i = 0;
	while (player[i])
		i++;
	if (!read_champion_header(av, &(player[i]), fd))
		return (0);
	size = 0;
	while (read(fd, &((player[i]->code)[size]), 1) && size <= CHAMP_MAX_SIZE)
		size++;
	if (size > CHAMP_MAX_SIZE || size != player[i]->prog_size)
		return (error2("Error: champion ", av, " is of wrong size"));
	player[i]->id = *id;
	*id = 0;
	return (1);
}
