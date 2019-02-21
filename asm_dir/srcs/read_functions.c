/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:55:18 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/17 15:18:08 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	ft_read_ws(int fd)
{
	char	c;
	int		ret;

	c = ' ';
	while (c == ' ' || c == '\t')
	{
		ret = read(fd, &c, 1);
		if (ret == -1)
			ft_putstr(strerror(errno));
		if (ret == 0)
			return (0);
	}
	return (c);
}

void	ft_skip_comment(int fd)
{
	char	c;
	int		ret;

	c = 0;
	while (c != '\n')
	{
		ret = read(fd, &c, 1);
		if (ret == 0)
			break ;
		if (ret == -1)
			ft_putstr(strerror(errno));
	}
	if (c == '\n')
		g_line_number++;
}

int		ft_isliteral(int c)
{
	if (ft_isascii(c) && c != '\"')
		return (1);
	return (0);
}

char	*ft_read_string(int fd, size_t size, int (*check)(int c))
{
	char	*str;
	int		ret;
	size_t	i;

	i = 0;
	str = (char*)malloc(size + 1 * sizeof(char));
	ft_bzero(str, size + 1);
	while (i < size && (ret = read(fd, &str[i], 1) > 0))
	{
		if (str[i] == '\n')
			g_line_number++;
		if (check(str[i]) == 0)
			break ;
		i++;
	}
	if (ret == -1)
		ft_putstr(strerror(errno));
	if (ret)
		lseek(fd, -1, SEEK_CUR);
	str[i] = '\0';
	return (str);
}

int		ft_check_endline(int fd)
{
	char	c;

	c = ft_read_ws(fd);
	if (c == '#' || c == '\n' || c == 0)
	{
		if (c == '#')
			ft_skip_comment(fd);
		else if (c == '\n')
			g_line_number++;
		return (1);
	}
	else
		return (0);
}
