/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:08:50 by marvin            #+#    #+#             */
/*   Updated: 2019/02/16 17:21:16 by marvin           ###   ########.fr       */
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

static char		*ft_parse_cmds(char *str, t_cmd *cmd)
{
	char	*cmds[17];
	char	*end_of_cmd;
	int		i;
	char	*tmp;

	i = -1;
	end_of_cmd = NULL;
	while (str[++i])
		if ((str[i] == ' ' || str[i] == '\t' || str[i] == '%') &&
				(end_of_cmd = str + i))
			break ;
//	if (!end_of_cmd) Error not cmd
	i = -1;
	tmp = ft_strsub(str, 0, end_of_cmd - str);
	ft_init_cmd_array(cmds);
	while (cmds[++i])
		if (!ft_strcmp(cmds[i], tmp))
			cmd->opcode = i + 1;
//	if (cmd->opcode == 0) Error false cmd
	free(tmp);
	return (ft_strdup(end_of_cmd + 1));
}

static char		*ft_parse_args(char *str, t_cmd *cmd)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_strsplit(str, SEPARATOR_CHAR);
	while (args[i])
	{
		cmd->args[i] = args[i];
		i++;
	}
	free(args);
	return (str);
}

static t_cmd	*ft_parse_line(char *str, int num)
{
	t_cmd	*cmd;

	cmd = ft_cmd_creator();
	cmd->num = num;
	str = ft_trim_and_exec_cmd(ft_parse_label, str, cmd);
	str = ft_trim_and_exec_cmd(ft_parse_cmds, str, cmd);
	str = ft_trim_and_exec_cmd(ft_parse_args, str, cmd);
	return (cmd);
}

t_list			*ft_parse_exec_code(int fd)
{
	char	*str;
	t_list	*lst;
	t_list	*tmp;
	t_cmd	*cmd_tmp;
	int		num;

	num = 0;
	lst = NULL;
	while (get_next_line(fd, &str))
	{
		if ((cmd_tmp = ft_parse_line(str, num)) != NULL)
		{
			num++;
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
