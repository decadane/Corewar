/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:31:50 by marvin            #+#    #+#             */
/*   Updated: 2019/02/14 18:19:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_cmd	*ft_cmd_destroyer(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (cmd->args[i])
			free(cmd->args[i]);
		else
			break ;
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (cmd->args_type[i])
			free(cmd->args_type[i]);
		else
			break ;
		i++;
	}
	free(cmd);
	return (NULL);
}
