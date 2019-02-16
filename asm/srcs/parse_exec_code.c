/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:08:50 by marvin            #+#    #+#             */
/*   Updated: 2019/02/16 13:42:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*ft_parse_label(char *str, t_cmd *cmd)
{
	char	*end_of_label;
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(end_of_label = ft_strchr(str, LABEL_CHAR)))
	{
		cmd->label = NULL;
		return (ft_strdup(str));
	}
	if (*(end_of_label - 1) == '%')
	{
		cmd->label = NULL;
		return (ft_strdup(str));
	}
	tmp = ft_strsub(str, 0, end_of_label - str);
	while (tmp[i])
	{
		if (ft_strchr(LABEL_CHARS, tmp[i]))
			i++;
		//Output error Label contains forbidden chars
	}
	cmd->label = tmp;
	return (ft_strdup(str + i + 1));
}

static t_cmd	*ft_parse_line(char *str)
{
	t_cmd	*cmd;
	char	*tmp;

	tmp = str;
	str = ft_strtrim(str);
	free(tmp);
	cmd = ft_cmd_creator();
	tmp = str;
	str = ft_parse_label(str, cmd);
	free(tmp);
	free(str);
/*	tmp = str;
	str = ft_strtrim(str);
	free(tmp);
	str = ft_parse_cmds(str, cmd);
	tmp = str;
	str = ft_strtrim(str);
	free(tmp);
	str = ft_parse_args(str, cmd);
*/	return (cmd);
}

t_list			*ft_parse_exec_code(int fd)
{
	char	*str;
	t_list	*lst;
	t_list	*tmp;
	t_cmd	*cmd_tmp;

	lst = NULL;
	while (get_next_line(fd, &str))
	{
		if ((cmd_tmp = ft_parse_line(str)) != NULL)
		{
			tmp = ft_lstnew(cmd_tmp, sizeof(t_cmd));
			ft_lstradd(&lst, tmp);
			free(cmd_tmp);
		}
		else
			free(str);
		//Output error Parse = NULL
		tmp = NULL;
	}
	return (lst);
}
