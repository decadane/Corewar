/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:08:50 by marvin            #+#    #+#             */
/*   Updated: 2019/02/18 18:44:39 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*ft_parse_label(char *str, t_cmd *cmd)
{
	char	*end_of_label;
	char	*tmp;
	size_t	i;

	if (!(end_of_label = ft_strchr(str, LABEL_CHAR)))
	{
		cmd->label = NULL;
		return (ft_strdup(str));
	}
	if (*(end_of_label - 1) == DIRECT_CHAR)
	{
		cmd->label = NULL;
		return (ft_strdup(str));
	}
	tmp = ft_strsub(str, 0, end_of_label - str);
	i = 0;
	while (tmp[i])
	{
		if (ft_strchr(LABEL_CHARS, tmp[i]) || tmp[i] == '\t')
			i++;
		else
			ft_error_output("Error label contains forbidden char");
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
	i = -1;
	if (!end_of_cmd)
	{
		cmd->size = 0;
		return (NULL);
	}
	tmp = ft_strsub(str, 0, end_of_cmd - str);
	ft_init_cmd_array(cmds);
	while (cmds[++i])
		if (!ft_strcmp(cmds[i], tmp))
			cmd->opcode = i + 1;
	(cmd->opcode == 0) ? (ft_error_output("Error false cmd")) : 0;
	free(tmp);
	return (ft_strdup(end_of_cmd));
}

static char		*ft_parse_args(char *str, t_cmd *cmd)
{
	char	**args;
	int		i;
	char	*tmp;
	char	*arg;

	i = 0;
	tmp = str;
	args = ft_strsplit(str, SEPARATOR_CHAR);
	while (args[i])
	{
		arg = args[i];
		arg = ft_strtrim(args[i]);
		free(args[i]);
		if (ft_check_arg(&arg) == 0)
			ft_error_output("Invalid argument");
		cmd->args[i] = arg;
		if ((tmp = ft_strchr(tmp, SEPARATOR_CHAR)))
			tmp++;
		i++;
	}
	free(args);
	if (tmp && *tmp != '#')
		ft_error_output("Error undefined char");
	return (tmp);
}

static t_cmd	*ft_parse_line(char *str)
{
	t_cmd	*cmd;

	cmd = ft_cmd_creator();
	str = ft_trim_and_exec_cmd(ft_parse_label, str, cmd);
	str = ft_trim_and_exec_cmd(ft_parse_cmds, str, cmd);
	if (str)
		str = ft_trim_and_exec_cmd(ft_parse_args, str, cmd);
	return (cmd);
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
		if (!ft_check_comment(str) && (cmd_tmp = ft_parse_line(str)))
		{
			tmp = ft_lstnew(cmd_tmp, sizeof(t_cmd));
			ft_lstradd(&lst, tmp);
			free(cmd_tmp);
		}
		else
			free(str);
		tmp = NULL;
		if (cmd_tmp == NULL)
			ft_error_output("Error parse = NULL\n");
		g_line_number++;
	}
	return (lst);
}
