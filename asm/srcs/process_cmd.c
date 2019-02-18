/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:56:00 by marvin            #+#    #+#             */
/*   Updated: 2019/02/18 18:36:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_check_endl(char *str)
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

static void		ft_parse_arg(t_cmd *cmd, int i)
{
	char	*command;
	int		j;

	command = cmd->args[i];
	while (*command == ' ' || *command == '\t')
		command++;
	if (*command == 'r' || *command == DIRECT_CHAR)
	{
		if (*command == 'r' && (ft_atoi(command + 1) == 0 ||
					ft_atoi(command + 1) > REG_NUMBER))
			ft_error_output("Error reg number");
		command++;
	}
	if (*command == LABEL_CHAR)
		return ;
	j = *command == '-' ? 1 : 0;
	while (command[j] && ft_isdigit(command[j]))
		j++;
	if (!ft_check_endl(&command[j]))
			ft_error_output("Error forbidden char");
	cmd->pargs[i] = ft_atoi(command);
	free(cmd->args[i]);
	cmd->args[i] = NULL;
}

static void		ft_first_process_cmd(t_cmd *cmd)
{
	char	cmds[17];
	int		i;
	int		cmds_num[17];

	i = 0;
	ft_init_args_array(cmds);
	ft_init_nums_array(cmds_num);
	while (i < 3)
/*	{
		if (cmd->args[i] && ft_check_arg_type(cmd, i) &&
				i <= cmds_num[cmd->opcode - 1])
			ft_parse_arg(cmd, i);
		else if (i > cmds_num[cmd->opcode - 1] && cmd->args[i])
			ft_error_output("Error arg type is forbidden");
		else
			cmd->codage <<= 2;
		i++;
	}*/
	{
		if (i + 1 <= cmds_num[cmd->opcode - 1] && cmd->args[i])
		{
			if (ft_check_arg_type(cmd, i))
				ft_parse_arg(cmd, i);
			else
				ft_error_output("Error arg type is forbidden");
		}
		else if (i + 1 > cmds_num[cmd->opcode - 1] && !cmd->args[i])
			cmd->codage <<= 2;
		else
			ft_error_output("Error num of args");
		i++;
	}
}

static int		ft_find_label(char *str, t_list *lbl_lst)
{
	t_label	*lbl;

	while (lbl_lst)
	{
		lbl = ((t_label*)lbl_lst->content);
		if (!ft_strcmp(str, lbl->name))
			return (lbl->offset);
		lbl_lst = lbl_lst->next;
	}
	ft_error_output("Error undefined label");
	return (0);
}

static void		ft_second_process_cmd(t_cmd *cmd, t_list *lbl_lst, int *pos)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < 3)
	{
		tmp = cmd->args[i];
		if (cmd->args[i])
		{
			if (*(cmd->args[i]) == DIRECT_CHAR)
				cmd->args[i]++;
			if (*(cmd->args[i]) == LABEL_CHAR)
				cmd->args[i]++;
			else
				ft_error_output("Error undefined char\n");
			cmd->pargs[i] = ft_find_label(cmd->args[i], lbl_lst) - *pos;
			cmd->args[i] = NULL;
			free(tmp);
		}
		i++;
	}
	*pos += cmd->size;
}

t_list			*ft_process_lst(t_list *lst, t_list *lbl_lst, int i)
{
	t_cmd	*cmd;
	t_list	*head;
	int		pos;

	pos = 0;
	head = lst;
	cmd = (t_cmd*)lst->content;
	while (lst)
	{
		if (i == 1)
			ft_first_process_cmd((t_cmd*)lst->content);
		else
			ft_second_process_cmd((t_cmd*)lst->content, lbl_lst, &pos);
		lst = lst->next;
		g_line_number++;
	}
	return (head);
}
