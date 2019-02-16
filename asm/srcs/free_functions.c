/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:31:50 by marvin            #+#    #+#             */
/*   Updated: 2019/02/16 13:37:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
/*
t_cmd	*ft_cmd_destroyer(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (label)
		free(label);
	while (i < 3)
	{
		if (cmd->args[i])
			free(cmd->args[i]);
		else
			break ;
		i++;
	}
	free(cmd);
	return (NULL);
}

void	ft_cmd_destroyer(void *node, size_t size)
{
	t_cmd	*cmd;
	int		i;

	(void)size;
	i = 0;
	cmd = (t_cmd*)node;
	if (cmd->label)
	{
		free(cmd->label);
		cmd->label = NULL;
	}
	while (i < 3)
	{
		if (cmd->args[i])
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
		}
		else
			break ;
		i++;
	}
	free(cmd);
}
*/
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
