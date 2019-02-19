/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:51:44 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/19 13:35:26 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int argc, char **argv)
{
	t_collect	*collect;
	char		*filename;
	int			i;

	if (argc == 1)
		ft_putendl(USAGE);
	i = 1;
	while (i < argc)
	{
		filename = ft_check_filename(argv[i]);
		collect = ft_create_collect();
		ft_read_file(argv[i], collect);
		ft_write_file(collect, filename);
		ft_free_collect(collect);
		i++;
	}
	return (0);
}
