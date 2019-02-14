/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:20:07 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/14 19:29:22 by marvin           ###   ########.fr       */
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
# include "libft.h"

typedef struct		s_cmd
{
	char			*name;
	unsigned char	opcode;
	unsigned char	codage;
	char			*args[3];
	char			*args_type[3];
	unsigned char	cmd_size;
}					t_cmd;

typedef struct		s_collect
{
	char			*bot_name;
	char			*bot_comment;
	unsigned		code_size;
	char			*bot_code;
}					t_collect;

typedef struct		s_label
{
	char			*name;
	unsigned		offset;
	char			value;
}					t_label;

//-------------kmedhurs--------------------
////--------alloc_funcs--------------------

t_cmd				*ft_cmd_creator(void);

////---------free_funcs--------------------

t_cmd				*ft_cmd_destroyer(t_cmd *cmd);

t_cmd				*ft_parse_cmd_line(char *str);
char				*ft_find_separator(char *str);
void				ft_init_cmd_array(char *arr[17]);

////---------DELETE_THIS_FUNKS!!!----------

void				print_cmd(t_cmd *cmd);

//-------------ffahey--------------------

#endif
