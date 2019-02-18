/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:31:50 by marvin            #+#    #+#             */
/*   Updated: 2019/02/17 18:38:16 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_cmd_destroyer(void *node, size_t size)
{
	t_cmd	*cmd;
	int		i;

	i = -1;
	cmd = (t_cmd*)node;
	if (cmd->label)
	{
		free(cmd->label);
		cmd->label = NULL;
	}
	while (++i < 3)
	{
		if (cmd->args[i])
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
		}
		else
			continue ;
	}
	bzero(node, size);
	free(cmd);
}

void	ft_lbl_destroyer(void *node, size_t size)
{
	bzero(node, size);
	free(node);
}

void	ft_del_label(void *ptr, size_t size)
{
	free(((t_label*)ptr)->name);
	ft_bzero(ptr, size);
	free(ptr);
}

void	ft_free_collect(t_collect *col)
{
	ft_bzero(col->bot_name, sizeof(col->bot_name));
	ft_bzero(col->bot_comment, sizeof(col->bot_comment));
	col->bot_size = 0;
	free(col->bot_code);
	ft_lstdel(&col->labels, ft_del_label);
	free(col);
}
