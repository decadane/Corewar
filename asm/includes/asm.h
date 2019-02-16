/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:20:07 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/16 13:37:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <unistd.h>
# include <stdio.h> //DELETE!
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft.h"
# include "op.h"

typedef struct		s_cmd
{
	char			*label;
	unsigned char	opcode;
	unsigned char	codage;
	char			*args[3];
	unsigned char	pargs[3];
	unsigned char	size;
	int				num;
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

//t_cmd				*ft_cmd_destroyer(t_cmd *cmd);
void				ft_cmd_destroyer(void *lst, size_t size);

t_list				*ft_parse_exec_code(int fd);

////---------DELETE_THIS_FUNKS!!!----------

void				print_cmd(t_cmd *cmd);
void				print_cmd_list(t_list *lst);

//-------------ffahey--------------------

#endif
