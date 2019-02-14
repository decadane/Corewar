/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:20:07 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/14 15:48:49 by ffahey           ###   ########.fr       */
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
	char			*agrs[3];
	char			*agrs_type[3];
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


//-------------ffahey--------------------

#endif
