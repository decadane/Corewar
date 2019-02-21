/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 19:02:59 by ffahey            #+#    #+#             */
/*   Updated: 2019/01/18 17:27:52 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_file	*find_fd(t_file **head, int fd)
{
	t_file	*file;

	file = *head;
	while (file)
	{
		if (file->fd == fd)
			return (file);
		file = file->next;
	}
	if (!file && (file = (t_file*)malloc(sizeof(t_file))))
	{
		file->str = NULL;
		file->fd = fd;
		file->next = *head;
		*head = file;
	}
	return (file);
}

static int		check_str(char **str, char **line)
{
	char	*endline;
	char	*tmp_str;

	endline = ft_strchr(*str, '\n');
	if (endline == NULL)
		return (0);
	*endline = '\0';
	if (!(*line = ft_strdup(*str)))
		return (-1);
	if (!(tmp_str = ft_strdup(endline + 1)))
	{
		ft_memdel((void**)line);
		return (-1);
	}
	ft_memdel((void**)str);
	*str = tmp_str;
	return (1);
}

static int		read_fd(int fd, char **save_buffer, char *buffer, char **line)
{
	int		ret;
	char	*tmp_str;
	char	check_res;

	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (*save_buffer)
		{
			tmp_str = *save_buffer;
			if (!(*save_buffer = ft_strjoin(tmp_str, buffer)))
				return (-1);
			ft_memdel((void**)&tmp_str);
		}
		else if (!(*save_buffer = ft_strdup(buffer)))
			return (-1);
		if ((check_res = check_str(save_buffer, line)))
			return (check_res);
	}
	return (ret);
}

int				get_next_line(int fd, char **line)
{
	static t_file	*file;
	t_file			*this;
	char			*buffer;
	int				ret;
	int				check_res;

	if (fd < 0 || !line || read(fd, &buffer, 0) < 0 ||
			!(this = find_fd(&file, fd)))
		return (-1);
	if (this->str && (check_res = check_str(&(this->str), line)))
		return (check_res);
	if (BUFF_SIZE <= 0 || !(buffer = (char*)malloc(BUFF_SIZE + 1)))
		return (-1);
	ret = read_fd(fd, &(this->str), buffer, line);
	free(buffer);
	if (ret == 0 && this->str && *(this->str) != '\0')
	{
		if (!(*line = ft_strdup(this->str)))
			return (-1);
		ft_memdel((void**)(&(this->str)));
		return (1);
	}
	if (ret <= 0 && *line)
		*line = NULL;
	return (ret);
}
