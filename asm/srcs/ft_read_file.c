/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:39:39 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/15 16:48:58 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_read_name(t_collect *col, char *cmd, unsigned char *flag)
{
	int	i;

	if (*flag & 0xf0)
		ft_error_output("double \".name\" comand");
	cmd += ft_strlen(NAME_CMD_STRING);
	while (*cmd == ' ' || *cmd == '\t')
		cmd++;
	if (*cmd == '\"')
	{
		cmd++;
		i = 0;
		while (cmd[i] != '\"')
		{
			if (cmd[i] == '\0')
				ft_error_output("Error1 \".name\" command");
			else
				i++;
		}
		ft_strncpy(col->bot_name, cmd, ft_min_int(i, PROG_NAME_LENGTH));
		*flag |= 0xf0;
	}
	else
		ft_error_output("Error2 \".name\" command");
}

static void	ft_read_comment(t_collect *col, char *cmd, unsigned char *flag)
{
	int	i;

	if (*flag & 0x0f)
		ft_error_output("double \".comment\" comand");
	cmd += ft_strlen(COMMENT_CMD_STRING);
	while (*cmd == ' ' || *cmd == '\t')
		cmd++;
	if (*cmd == '\"')
	{
		cmd++;
		i = 0;
		while (cmd[i] != '\"')
		{
			if (cmd[i] == '\0')
				ft_error_output("Error \".comment\" command");
			else
				i++;
		}
		ft_strncpy(col->bot_comment, cmd, ft_min_int(i, COMMENT_LENGTH));
		*flag |= 0x0f;
	}
	else
		ft_error_output("Error \".comment\" command");
}

static void	ft_header(int fd, t_collect *col)
{
	char			*data;
	char			*cmd;
	unsigned char	flag;

	flag = 0;
	while (get_next_line(fd, &data) > 0)
	{
		cmd = data;
		while (*cmd == ' ' || *cmd == '\t')
			cmd++;
		if (*cmd == '#')
		{
			free(data);
			continue ;
		}
		if (*cmd && !ft_strncmp(cmd, NAME_CMD_STRING,
					ft_strlen(NAME_CMD_STRING)))
			ft_read_name(col, cmd, &flag);
		else if (*cmd && !ft_strncmp(cmd, COMMENT_CMD_STRING,
					ft_strlen(COMMENT_CMD_STRING)))
			ft_read_comment(col, cmd, &flag);
		free(data);
		if (flag == 0xff)
			return ;
	}
}

void		ft_read_file(char *filename, t_collect *col)
{
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_putstr(strerror(errno));
	ft_header(fd, col);
	close(fd);
}
