/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 03:06:10 by trhogoro          #+#    #+#             */
/*   Updated: 2019/02/18 16:00:10 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		cmd_get_data(void *src, int start, int len)
{
	unsigned int	result;
	int				i;

	i = len;
	result = 0;
	while (i)
	{
		result *= 256;
		result += ((unsigned char *)src)[(start + len - i) % MEM_SIZE];
		i--;
	}
	return (result);
}

void	cmd_set_data(char *dst, int start, char *src, int len)
{
	int i;

	i = len;
	while (i--)
		*(dst + (start + i) % MEM_SIZE) = *src++;
}

void	cmd_set_color(char *dst, int start, char color, int len)
{
	while (len--)
		*(dst + (start + len) % MEM_SIZE) = color;
}

int		cmd_get_int(t_vm *arena, t_process *proc, int src_type, int *shift)
{
	int		reg;
	short	ind;

	if (src_type == A_REG)
	{
		reg = cmd_get_data(arena->map, proc->pc + *shift, 1);
		if (reg <= 0 || reg > REG_NUMBER)
			return (*shift = ERR_FLAG);
		*shift += 1;
		return (proc->registry[reg - 1]);
	}
	if (src_type == A_IND)
	{
		ind = ((short)cmd_get_data(arena->map, proc->pc + *shift, 2)) % IDX_MOD;
		*shift += 2;
		return (cmd_get_data(arena->map, (proc->pc + ind) % MEM_SIZE, 4));
	}
	if ((src_type == A_DIR) && (*shift = *shift + 4))
		return (cmd_get_data(arena->map, (proc->pc + *shift - 4) %
		MEM_SIZE, 4));
		if ((src_type == A_DIR2) && (*shift = *shift + 2))
		return (cmd_get_data(arena->map, (proc->pc + *shift - 2) %
		MEM_SIZE, 2));
}

void	cmd_aff(t_vm *arena, t_process *proc)
{
	char	value;
	int		reg;

	if (proc->op_arg != 0x40)
		return (wrong_argument(proc));
	reg = cmd_get_data(arena->map, proc->pc + 2, 1);
	if (reg <= 0 || reg > REG_NUMBER)
		return (wrong_argument(proc));
	value = (char)proc->registry[reg - 1];
	if (arena->aff)
		ft_putchar(value);
	proc->pc = (unsigned short)((proc->pc + 3) % MEM_SIZE);
}
