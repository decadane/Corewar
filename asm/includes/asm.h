/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:20:07 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/17 17:49:32 by marvin           ###   ########.fr       */
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
	int				pargs[3];
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
	int				offset;
}					t_label;

//-------------kmedhurs--------------------
////--------alloc_funcs--------------------

t_cmd				*ft_cmd_creator(void);
t_label				*ft_lbl_creator(void);

////---------free_funcs--------------------

void				ft_cmd_destroyer(void *lst, size_t size);
void				ft_lbl_destroyer(void *node, size_t size);

void				ft_init_cmd_array(char *arr[17]);
t_list				*ft_parse_exec_code(int fd);
char				*ft_trim_and_exec_cmd(char *(*funk)(char *str, t_cmd *cmd),
		char *str, t_cmd *cmd);
char				ft_check_arg_type(t_cmd *cmd, int i);
void				ft_init_args_array(char cmds[17]);
int					ft_check_comment(char *str);
t_list				*ft_collect_labels(t_list *lst);
char				*ft_process_to_bytecode(t_list *lst, unsigned*);//, t_collect *col);
unsigned			ft_find_result_len(t_list *lst);

t_list				*ft_process_lst(t_list *lst, t_list *lables, int i);

////---------DELETE_THIS_FUNKS!!!----------

void				print_cmd(t_cmd *cmd);
void				print_cmd_list(t_list *lst);
void				print_lbl(t_label *lbl);
void				print_lbl_list(t_list *lst);

//-------------ffahey--------------------

void				ft_error_output(char *str);

#endif
