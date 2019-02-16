/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:08:56 by marvin            #+#    #+#             */
/*   Updated: 2019/02/15 15:29:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_cmd	*ft_cmd_creator(void)
{
	t_cmd	*cmd;

	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		exit(-20);
	cmd->label = NULL;
	cmd->opcode = 0;
	cmd->codage = 0;
	cmd->args[0] = NULL;
	cmd->args[1] = NULL;
	cmd->args[2] = NULL;
	cmd->pargs[0] = 0;
	cmd->pargs[1] = 0;
	cmd->pargs[2] = 0;
	cmd->size = 0;
	cmd->num = 0;
	return (cmd);
}
