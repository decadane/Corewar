/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:28:44 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/18 21:38:12 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_print_memory(unsigned char *mem, unsigned char *colors, size_t size)
{
	int				i;
	unsigned char	color;

	color = 0;
	i = -1;
	while (++i < size)
	{
		if (colors[i] != color)
		{
			color = colors[i];
			(!color) ? write(1, "\033[0m", 4) : (void)0;
			(color == 1) ? write(1, "\033[31m", 5) : (void)0;
			(color == 2) ? write(1, "\033[32m", 5) : (void)0;
			(color == 3) ? write(1, "\033[33m", 5) : (void)0;
			(color == 4) ? write(1, "\033[34m", 5) : (void)0;
		}
		ft_putchar((*mem >> 4) + ((*mem >> 4) > 9 ? 'A' - 10 : '0'));
		ft_putchar((*mem & 0xf) + ((*mem & 0xf) > 9 ? 'A' - 10 : '0'));
		ft_putchar(' ');
		mem++;
		(!((i + 1) % 32)) ? ft_putendl("") : (void)0;
	}
}

void	ft_print_stat(t_vm *arena)
{
	int	i;

	ft_putstr("\n\n---------------");
	ft_printf("\nTotal cycles passed: %d\n", arena->cycles_passed);
	ft_printf("Maximum processes run %d\n", arena->max_procs);
	i = 0;
	while (arena->players[i]->id != arena->cur_win_id)
		i++;
	ft_printf("The winer reported 'alive' %d times\n",
		arena->players[i]->tot_lives);
}
