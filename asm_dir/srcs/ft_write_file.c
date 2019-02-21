/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 17:51:35 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/19 13:55:36 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_reverse_write(int fd, void *ptr, size_t size)
{
	size_t i;

	i = 0;
	while (size--)
		write(fd, (char*)ptr + size, 1);
}

static void	ft_write_to_file(int fd, t_collect *col)
{
	int		magic;
	int		zero;

	magic = COREWAR_EXEC_MAGIC;
	zero = 0x00000000;
	ft_reverse_write(fd, &magic, sizeof(magic));
	write(fd, col->bot_name, PROG_NAME_LENGTH);
	write(fd, &zero, sizeof(zero));
	ft_reverse_write(fd, &col->bot_size, sizeof(col->bot_size));
	write(fd, col->bot_comment, COMMENT_LENGTH);
	write(fd, &zero, 4);
	write(fd, col->bot_code, col->bot_size);
}

void		ft_write_file(t_collect *col, char *filename)
{
	int		fd;
	char	*output_filename;

	output_filename = ft_strjoin(filename, ".cor");
	free(filename);
	fd = open(output_filename, O_CREAT | O_WRONLY | O_TRUNC,
			S_IREAD | S_IWRITE);
	if (fd == -1)
	{
		ft_putstr(output_filename);
		ft_putstr(": ");
		ft_putendl(strerror(errno));
		exit(0);
	}
	ft_write_to_file(fd, col);
	ft_putstr("Writing output program to ");
	ft_putendl(output_filename);
	free(output_filename);
	close(fd);
}
