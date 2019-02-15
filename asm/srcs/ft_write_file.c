/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 17:51:35 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/15 18:59:54 by ffahey           ###   ########.fr       */
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

void	ft_get_botcode(t_collect *col)
{
	col->bot_code = (char*)malloc(col->bot_size * sizeof(char));
}

void	ft_write_file(t_collect *col, char *filename)
{
	int		fd;
	char	*output_filename;
	int		magic;
	int		zero;
	char	bot_code[] = {9, 0, 0x18, 2, 0x90, 0, 0, 0, 1, 2, 2, 0x90, 0, 0, 0, 0};

	output_filename = ft_strjoin(filename, ".cor");
	fd = open(output_filename, O_CREAT | O_WRONLY | O_TRUNC, S_IREAD | S_IWRITE);
	if (fd == -1)
		ft_putstr(strerror(errno));
	magic = COREWAR_EXEC_MAGIC;
	zero = 0xaaaaaaaa;
	ft_reverse_write(fd, &magic, sizeof(magic));
	write(fd, col->bot_name, PROG_NAME_LENGTH);
	write(fd, &zero, 4);
	col->bot_size = 0x10;
	ft_reverse_write(fd, &col->bot_size, sizeof(col->bot_size));
	write(fd, col->bot_comment, COMMENT_LENGTH);
	write(fd, &zero, 4);
	write(fd, bot_code, 16);
	close(fd);
}
