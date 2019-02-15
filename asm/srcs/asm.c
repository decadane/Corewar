/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:51:44 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/15 18:06:11 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int argc, char **argv)
{
	t_collect	*collect;
	char		*filename;

	if (argc != 2)
		return (1);
	filename = ft_check_filename(argv[1]);
	collect = ft_create_collect();
	ft_read_file(argv[1], collect);
	printf("name: %s\n", collect->bot_name);
	printf("comment: %s\n", collect->bot_comment);
	ft_write_file(collect, filename);
	ft_free_collect(collect);
	return (0);
}
