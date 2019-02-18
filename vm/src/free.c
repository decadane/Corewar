/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 13:20:17 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/15 17:49:42 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		free_players(t_player **res)
{
	int i;

	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);
	res = NULL;
	return (0);
}

int		free_procs(t_list *proc)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (proc)
	{
		tmp = proc->next;
		free(proc->content);
		free(proc);
		proc = tmp;
	}
	return (0);
}

void	free_arena(t_vm *arena)
{
	free_players(arena->players);
	free_procs(arena->procs);
	free(arena);
}
