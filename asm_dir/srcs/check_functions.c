/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:30:31 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/18 18:35:05 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

int			ft_check_endl(char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
			str++;
		else if (*str == COMMENT_CHAR)
			return (1);
		else
			return (0);
	}
	return (1);
}

int			ft_check_arg(char **arg)
{
	char *end_arg;
	char *new_arg;

	end_arg = *arg;
	if (*end_arg == DIRECT_CHAR)
		end_arg++;
	if (*end_arg == LABEL_CHAR || *end_arg == '-')
		end_arg++;
	while (*end_arg && ft_strchr(LABEL_CHARS, *end_arg))
		end_arg++;
	if (ft_check_endl(end_arg))
	{
		new_arg = ft_strsub(*arg, 0, end_arg - *arg);
		free(*arg);
		*arg = new_arg;
		return (1);
	}
	else
		return (0);
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
