/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffahey <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:20:07 by ffahey            #+#    #+#             */
/*   Updated: 2019/02/17 21:00:51 by ffahey           ###   ########.fr       */
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
# include <errno.h>
# include "libft.h"
# include "op.h"

# define C(a) printf("check%d\n", a);

extern unsigned		g_line_number;

typedef struct		s_cmd
{
	char			*label;
	unsigned char	opcode;
	unsigned char	codage;
	char			*args[3];
	int				pargs[3];
	unsigned char	size;
}					t_cmd;

typedef struct		s_label
{
	char			*name;
	int				offset;
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
////--------alloc_funcs--------------------

t_cmd				*ft_cmd_creator(void);
t_label				*ft_lbl_creator(void);

////---------free_funcs--------------------

void				ft_cmd_destroyer(void *lst, size_t size);
void				ft_lbl_destroyer(void *node, size_t size);

////---------init_funcs--------------------

void				ft_init_cmd_array(char *arr[17]);
void				ft_init_nums_array(int cmds[17]);
void				ft_init_args_array(char cmds[17]);

t_list				*ft_parse_exec_code(int fd);
char				*ft_trim_and_exec_cmd(char *(*funk)(char *str, t_cmd *cmd),
		char *str, t_cmd *cmd);
char				ft_check_arg_type(t_cmd *cmd, int i);
int					ft_check_comment(char *str);
t_list				*ft_collect_labels(t_list *lst);
void				ft_process_to_bytecode(t_list *lst, t_collect *col);
unsigned			ft_find_result_len(t_list *lst);
void				ft_get_bot_code(int fd, t_collect *col);

t_list				*ft_process_lst(t_list *lst, t_list *lables, int i);

////---------DELETE_THIS_FUNKS!!!----------

void				print_cmd(t_cmd *cmd);
void				print_cmd_list(t_list *lst);
void				print_lbl(t_label *lbl);
void				print_lbl_list(t_list *lst);

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

void				ft_error_output(char *str);

#endif
