/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_process_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:02:42 by marvin            #+#    #+#             */
/*   Updated: 2019/02/16 18:17:00 by marvin           ###   ########.fr       */
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
		if (ft_isdigit(command[j]))
			j++;
//		else Error forbidden char in arg
	}
	cmd->pargs[i] = ft_atoi(command);
	free(cmd->args[i]);
	cmd->args[i] = NULL;
}

static t_cmd	*ft_first_process_cmd(t_cmd *cmd)	
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
	return (cmd);
}

t_list			*ft_first_process_lst(t_list *lst)
{
	t_cmd	*cmd;
	t_list	*head;

	head = lst;
	cmd = (t_cmd*)lst->content;
	while (lst)
	{
		ft_first_process_cmd((t_cmd*)lst->content);
		lst = lst->next;
	}
	return (head);
}
