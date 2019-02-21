/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:28:38 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/18 18:47:02 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		ft_init_cmd_array(char *arr[17])
{
	arr[0] = "live";
	arr[1] = "ld";
	arr[2] = "st";
	arr[3] = "add";
	arr[4] = "sub";
	arr[5] = "and";
	arr[6] = "or";
	arr[7] = "xor";
	arr[8] = "zjmp";
	arr[9] = "ldi";
	arr[10] = "sti";
	arr[11] = "fork";
	arr[12] = "lld";
	arr[13] = "lldi";
	arr[14] = "lfork";
	arr[15] = "aff";
	arr[16] = 0x0;
}

void		ft_init_args_array(char cmds[17])
{
	cmds[0] = 0x40;
	cmds[1] = 0x70;
	cmds[2] = 0x94;
	cmds[3] = 0x92;
	cmds[4] = 0x92;
	cmds[5] = 0xfe;
	cmds[6] = 0xfe;
	cmds[7] = 0xfe;
	cmds[8] = 0x40;
	cmds[9] = 0xfa;
	cmds[10] = 0x9f;
	cmds[11] = 0x40;
	cmds[12] = 0x70;
	cmds[13] = 0xfa;
	cmds[14] = 0x40;
	cmds[15] = 0x80;
	cmds[16] = 0x0;
}

void		ft_init_nums_array(int cmds[17])
{
	cmds[0] = 1;
	cmds[1] = 2;
	cmds[2] = 2;
	cmds[3] = 3;
	cmds[4] = 3;
	cmds[5] = 3;
	cmds[6] = 3;
	cmds[7] = 3;
	cmds[8] = 1;
	cmds[9] = 3;
	cmds[10] = 3;
	cmds[11] = 1;
	cmds[12] = 2;
	cmds[13] = 3;
	cmds[14] = 1;
	cmds[15] = 1;
	cmds[16] = 0;
}
