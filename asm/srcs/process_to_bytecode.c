/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_to_bytecode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 16:13:04 by marvin            #+#    #+#             */
/*   Updated: 2019/02/17 21:01:31 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		ft_without_codage(int *size, t_cmd *cmd)
{
	cmd->codage = 0;
	if (cmd->opcode == 1)
		size[0] = 4;
	else
		size[0] = 2;
}

static void		ft_reverse_arg(char *res, int size, int *i, int arg)
{
	int		j;

	j = 0;
	while (j < size)
	{
		res[*i] = *((char*)&arg + (size - 1) - j);
		j++;
		(*i)++;
	}
}

static void		ft_convert_codage(int *size, t_cmd *cmd)
{
	int		i;
	int		type;

	i = 0;
	if (cmd->opcode == 1 || cmd->opcode == 9 || cmd->opcode == 12 ||
			cmd->opcode == 15)
		ft_without_codage(size, cmd);
	while (i < 3 && cmd->codage)
	{
		type = (cmd->codage >> ((3 - i) * 2)) & 0x03;
		if (type == 0x01)
			size[i] = 1;
		else if (type == 0x02)
		{
			if (cmd->opcode > 8 && cmd->opcode < 16 && cmd->opcode != 13)
				size[i] = 2;
			else
				size[i] = 4;
		}
		else if (type == 0x03)
			size[i] = 2;
		else
			size[i] = 0;
		i++;
	}
}

static void		ft_convert_to_string(char *res, t_cmd *cmd, int *i)
{
	int		size[3];
	int		j;

	size[0] = 0;
	size[1] = 0;
	size[2] = 0;
	j = 0;
	res[*i] = cmd->opcode;
	(*i)++;
	ft_convert_codage(size, cmd);
	if (cmd->opcode != 1 && cmd->opcode != 9 && cmd->opcode != 12 &&
			cmd->opcode != 15)
		res[(*i)++] = cmd->codage;
	while (j < 3 && size[j] != 0)
	{
		ft_reverse_arg(res, size[j], i, cmd->pargs[j]);
		j++;
	}
}

void			ft_process_to_bytecode(t_list *lst, t_collect *col)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	col->bot_size = ft_find_result_len(lst);
	if (col->bot_size > CHAMP_MAX_SIZE)
		ft_error_output("Error champ is too large");
	if (!(col->bot_code = (char*)malloc(sizeof(char) * (col->bot_size + 1))))
		exit(-20);
	while (lst)
	{
		cmd = (t_cmd*)lst->content;
		ft_convert_to_string(col->bot_code, cmd, &i);
		lst = lst->next;
	}
}
