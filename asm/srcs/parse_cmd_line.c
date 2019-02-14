/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 17:13:21 by marvin            #+#    #+#             */
/*   Updated: 2019/02/14 19:38:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*ft_find_cmd(char *str, t_cmd *cmd)
{
	char	*cmds[17];
	int		i;
	char	*tmp;

	i = 0;
	ft_init_cmd_array(cmds);
	while (cmds[i])
	{
		tmp = ft_find_separator(str);
		if (tmp && (tmp = ft_strsub(str, 0, tmp - str)) &&
				 (!ft_strcmp(tmp, cmds[i])))
		{
			free(tmp);
			cmd->name = cmds[i];
			cmd->opcode = i + 1;
			tmp = ft_strdup(str + ft_strlen(cmds[i]));
			free(str);
			cmd->cmd_size += 1;
			return (tmp);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

static void		ft_add_codage_and_size(unsigned char *c, int a, t_cmd *cmd)
{
	*c += a;
	*c <<= 2;
	if (cmd->opcode != 1 &&
			cmd->opcode != 9 &&
			cmd->opcode != 12 &&
			cmd->opcode != 15)
		cmd->cmd_size += 1;
	if (a == 1)
		cmd->cmd_size += 1;
	else
		cmd->cmd_size += 4;
}

static int		ft_args_count(int opcode)
{
	if (opcode == 1 ||
			opcode == 9 ||
			opcode == 12 ||
			opcode == 15 ||
			opcode == 16)
		return (1);
	else if (opcode == 2 ||
			opcode == 3 ||
			opcode == 13)
		return (2);
	else
		return (3);
}

static char		*ft_find_args(char *str, t_cmd *cmd)
{
	char	**args;
	char	**tmp;
	int		i;

	i = 0;
	args = ft_strsplit(str, ',');
	tmp = args;
	while (args[i])
	{
		if (args[i][0] == 'r')
			ft_add_codage_and_size(&cmd->codage, 1, cmd);
		else if (args[i][0] == '%')
			ft_add_codage_and_size(&cmd->codage, 2, cmd);
		else
			ft_add_codage_and_size(&cmd->codage, 3, cmd);
		cmd->args[i] = ft_strdup(args[i]);
		i++;
	}
	ft_free_tab(&tmp);
	if (i == ft_args_count(cmd->opcode))
		return (str);
	else
		return (NULL);
}

t_cmd			*ft_parse_cmd_line(char *str)
{
	t_cmd	*cmd;	
	char	*tmp;

	cmd = ft_cmd_creator();
	str = ft_strtrim(str);
	if (!(str = ft_find_cmd(str, cmd)))
		return (ft_cmd_destroyer(cmd));
	tmp = ft_strtrim(str);
	free(str);
	str = tmp;
	if (!(str = ft_find_args(str, cmd)))
		return (ft_cmd_destroyer(cmd));
	free(str);
	print_cmd(cmd);
	return (cmd);
}
