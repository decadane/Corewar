/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:31:06 by marvin            #+#    #+#             */
/*   Updated: 2019/02/18 21:19:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*ft_trim_and_exec_cmd(char *(*funk)(char *str, t_cmd *cmd),
		char *str, t_cmd *cmd)
{
	char	*tmp;

	if (str && *str != '\0')
	{
		tmp = str;
		str = ft_strtrim(str);
		free(tmp);
	}
	tmp = str;
	str = funk(str, cmd);
	free(tmp);
	return (str);
}

unsigned	ft_find_result_len(t_list *lst)
{
	unsigned	res;

	res = 0;
	while (lst)
	{
		res += ((t_cmd*)lst->content)->size;
		lst = lst->next;
	}
	return (res);
}

char		*ft_label_or_cmd(t_cmd *cmd, char str)
{
	if (cmd->label && !str)
		cmd->size = 0;
	else
		ft_error_output("Error command without arguments");
	return (NULL);
}
