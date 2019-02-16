/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:20:07 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/16 18:45:25 by ffahey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include "libft.h"
# include "op.h"

# define C(a) printf("check%d\n", a);

typedef struct		s_line
{
	char			*label;
	char			*name;
	char			*agrs[3];
}					t_line;

typedef struct		s_cmd
{
	char			*label;
	unsigned char	opcode;
	unsigned char	codage;
	t_arg_type		arg_types[3];
	char			*args[3];
	unsigned char	size;
}					t_cmd;

typedef struct		s_label
{
	char			*name;
	unsigned		offset;
	char			value;
}					t_label;

typedef struct		s_collect
{
	char			bot_name[PROG_NAME_LENGTH + 1];
	char			bot_comment[COMMENT_LENGTH + 1];
	unsigned int	bot_size;
	char			*bot_code;
	t_list			*labels;
}					t_collect;


//-------------kmedhurs--------------------


//-------------ffahey--------------------
char				*ft_check_filename(char *str);
void				ft_error_output(char *str);
void				ft_free_collect(t_collect *col);
void				ft_del_label(void *ptr, size_t size);
t_collect			*ft_create_collect();
void				ft_read_file(char *filename, t_collect *col);
void				ft_write_file(t_collect *col, char *filename);
char				ft_read_ws(int fd);
int					ft_isliteral(int c);
char				*ft_read_string(int fd, size_t size, int (*check)(int c));
void				ft_skip_comment(int fd);
int					ft_check_endline(int fd);

#endif
