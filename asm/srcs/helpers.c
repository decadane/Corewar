/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:31:06 by marvin            #+#    #+#             */
/*   Updated: 2019/02/18 14:11:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

int			ft_check_comment(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
			str++;
		else if (*str == '#')
			return (1);
		else
			return (0);
	}
	return (1);
}

char		*ft_trim_and_exec_cmd(char *(*funk)(char *str, t_cmd *cmd),
		char *str, t_cmd *cmd)
{
	char	*tmp;

	if (str && *str != '\0')
	{
		tmp = str;
		str = ft_strtrim(str);
		free(tmp);
	}
	tmp = str;
	str = funk(str, cmd);
	free(tmp);
	return (str);
}

static void	ft_set_code(char *code, t_cmd *cmd, char value)
{
	if (cmd->opcode == 1 || cmd->opcode == 9 || cmd->opcode == 12 ||
			cmd->opcode == 15)
		cmd->size--;
	*code = value;
	if (value == REG_CODE)
	{
		cmd->size += 1;
		cmd->codage += 1;
		cmd->codage <<= 2;
	}
	else if (value == DIR_CODE)
	{
		if (cmd->opcode > 8 && cmd->opcode < 16 && cmd->opcode != 13)
			cmd->size += 2;
		else
			cmd->size += 4;
		cmd->codage += 2;
		cmd->codage <<= 2;
	}
	else
	{
		cmd->size += 2;
		cmd->codage += 3;
		cmd->codage <<= 2;
	}
}

char		ft_check_arg_type(t_cmd *cmd, int i)
{
	char	code;
	char	cmds[17];
	int		tmp;

	if (i == 0)
		tmp = 8;
	else if (i == 1)
		tmp = 5;
	else
		tmp = 2;
	ft_init_args_array(cmds);
	if (*(cmd->args[i]) == 'r')
		ft_set_code(&code, cmd, REG_CODE);
	else if (*(cmd->args[i]) == '%')
		ft_set_code(&code, cmd, DIR_CODE);
	else
		ft_set_code(&code, cmd, IND_CODE);
	return ((cmds[cmd->opcode - 1] >> (tmp - code)) & 1);
}

unsigned 	ft_find_result_len(t_list *lst)
{
	unsigned	res;

	res = 0;
	while (lst)
	{
		res += ((t_cmd*)lst->content)->size;
		lst = lst->next;
	}
	return (res);
}

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
	arr[16] = NULL;
}
//DELETE THIS

void		print_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	printf("Label: %s|\n", cmd->label);
	printf("Opcode: %d\n", cmd->opcode);
	printf("Codage: %x\n", cmd->codage);
	printf("Arg1: %s|\n", cmd->args[0]);
	printf("Arg2: %s|\n", cmd->args[1]);
	printf("Arg3: %s|\n", cmd->args[2]);
	printf("Parg1: %d|\n", cmd->pargs[0]);
	printf("Parg2: %d|\n", cmd->pargs[1]);
	printf("Parg3: %d|\n", cmd->pargs[2]);
	printf("Size: %d\n", cmd->size);
}

void		print_cmd_list(t_list *lst)
{
	while (lst)
	{
		print_cmd((t_cmd*)lst->content);
		lst = lst->next;
	}
}

void		print_lbl(t_label *lbl)
{
	if (!lbl)
		return ;
	printf("Label: %s|\n", lbl->name);
	printf("Offset: %d\n", lbl->offset);
}

void		print_lbl_list(t_list *lst)
{
	while (lst)
	{
		print_lbl((t_label*)lst->content);
		lst = lst->next;
	}
}
