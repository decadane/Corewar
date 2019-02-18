/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:51:01 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/18 18:21:52 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_collect	*ft_create_collect(void)
{
	t_collect	*col;

	col = (t_collect*)malloc(sizeof(t_collect));
	ft_bzero(col->bot_name, sizeof(col->bot_name));
	ft_bzero(col->bot_comment, sizeof(col->bot_comment));
	col->bot_size = 0;
	col->bot_code = NULL;
	col->labels = NULL;
	return (col);
}

t_label		*ft_lbl_creator(void)
{
	t_label	*lbl;

	if (!(lbl = (t_label*)malloc(sizeof(t_label))))
		exit(-20);
	lbl->name = NULL;
	lbl->offset = 0;
	return (lbl);
}

t_cmd		*ft_cmd_creator(void)
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
	cmd->size = 2;
	return (cmd);
}
