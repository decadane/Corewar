/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 13:02:59 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/17 18:50:15 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_read_name(int fd, t_collect *col, unsigned char *flag)
{
	char	c;
	char	*str;
	int		ret;

	if (*flag & 0xf0)
		ft_error_output("Double .name command");
	c = ft_read_ws(fd);
	if (c == '\"')
	{
		str = ft_read_string(fd, PROG_NAME_LENGTH, ft_isliteral);
		ret = read(fd, &c, 1);
		if (ret > 0 && c != '\"')
			ft_error_output("Invalid name length.");
		else if (ret == -1)
			ft_putstr(strerror(errno));
		if (ft_check_endline(fd) == 0)
			ft_error_output("Invalid command line");
		ft_strcpy(col->bot_name, str);
		free(str);
		*flag |= 0xf0;
	}
	else
		ft_error_output("Error command");
}

void	ft_read_comment(int fd, t_collect *col, unsigned char *flag)
{
	char	c;
	char	*str;
	int		ret;

	if (*flag & 0x0f)
		ft_error_output("Double .comment command");
	c = ft_read_ws(fd);
	if (c == '\"')
	{
		str = ft_read_string(fd, COMMENT_LENGTH, ft_isliteral);
		ret = read(fd, &c, 1);
		if (ret > 0 && c != '\"')
			ft_error_output("Invalid comment length");
		else if (ret == -1)
			ft_putstr(strerror(errno));
		if (ft_check_endline(fd) == 0)
			ft_error_output("Invalid command line");
		ft_strcpy(col->bot_comment, str);
		free(str);
		*flag |= 0x0f;
	}
	else
		ft_error_output("Error command");
}

void	ft_read_name_or_comment(int fd, t_collect *col, unsigned char *flag)
{
	char	*command;

	command = NULL;
	command = ft_read_string(fd, 10, ft_isalpha);
	if (ft_strcmp(command, NAME_CMD_STRING + 1) == 0)
		ft_read_name(fd, col, flag);
	else if (ft_strcmp(command, COMMENT_CMD_STRING + 1) == 0)
		ft_read_comment(fd, col, flag);
	else
		ft_error_output("Invalid command.");
	free(command);
}

void	ft_read_header(int fd, t_collect *col)
{
	char			c;
	unsigned char	flag;

	flag = 0x00;
	while (1)
	{
		c = ft_read_ws(fd);
		if (c == '#' || c == '\n')
		{
			if (c == '#')
				ft_skip_comment(fd);
			else
				g_line_number++;
			continue ;
		}
		else if (c == '.')
			ft_read_name_or_comment(fd, col, &flag);
		else if (flag != 0xff)
			ft_error_output("Invalid command line.");
		else
		{
			lseek(fd, -1, SEEK_CUR);
			break ;
		}
	}
}

void	ft_read_file(char *filename, t_collect *col)
{
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_putstr(strerror(errno));
	ft_read_header(fd, col);
	ft_get_bot_code(fd, col);
	close(fd);
}
