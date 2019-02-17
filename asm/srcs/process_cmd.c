/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:56:00 by marvin            #+#    #+#             */
/*   Updated: 2019/02/17 19:24:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		ft_parse_arg(t_cmd *cmd, int i)
{
	char	*command;
	int		j;

	j = 0;
	command = cmd->args[i];
	if (*command == 'r' || *command == DIRECT_CHAR)
		command++;
	if (*command == LABEL_CHAR)
		return ;
	while (command[j])
	{
		if (ft_isdigit(command[j]) || command[j] == ' ' || command[j] == '-')
			j++;
		else if (command[j] == '#')
			break ;
		else 
			ft_error_output("Error forbidden char");
	}
	cmd->pargs[i] = ft_atoi(command);
	free(cmd->args[i]);
	cmd->args[i] = NULL;
}

static void		ft_first_process_cmd(t_cmd *cmd)
{
	char	cmds[17];
	int		i;

	i = 0;
	ft_init_args_array(cmds);
	while (i < 3)
	{
		if (cmd->args[i] && ft_check_arg_type(cmd, i))
			ft_parse_arg(cmd, i);
//		else Error arg type is forbidden
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
	ft_error_output("Error undefined label\n");
	return (0);
}

static void		ft_second_process_cmd(t_cmd *cmd, t_list *lbl_lst, int *pos)
{
	int		i;
	char	*tmp;

	i = 0;
	*pos += cmd->size;
	while (i < 3)
	{
		tmp = cmd->args[i];
		if (cmd->args[i])
		{
			if (*(cmd->args[i]) == '%')
				cmd->args[i]++;
			if (*(cmd->args[i]) == ':')
				cmd->args[i]++;
			else
				ft_error_output("Error undefined char\n");
			cmd->pargs[i] = ft_find_label(cmd->args[i], lbl_lst) - *pos;
			cmd->args[i] = NULL;
			free(tmp);
		}
		i++;
	}
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
	}
	return (head);
}
