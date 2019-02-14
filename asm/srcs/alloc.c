/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:08:56 by marvin            #+#    #+#             */
/*   Updated: 2019/02/14 18:52:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_cmd	*ft_cmd_creator(void)
{
	t_cmd   *cmd;

	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		exit(-20);
	cmd->name = NULL;
	cmd->opcode = 0;
	cmd->codage = 0;
	cmd->args[0] = NULL;
	cmd->args[1] = NULL;
	cmd->args[2] = NULL;
	cmd->args_type[0] = NULL;
	cmd->args_type[1] = NULL;
	cmd->args_type[2] = NULL;
	cmd->cmd_size = 0;
	return (cmd);
}
