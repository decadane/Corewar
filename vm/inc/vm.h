/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:41:29 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/18 21:02:31 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "op.h"
# include "libft.h"

# define MAGIC 0xf383ea00

typedef struct	s_player
{
	short			id;
	unsigned int	start_point;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			code[CHAMP_MAX_SIZE];
	unsigned int	prog_size;
	unsigned int	tot_lives;
}				t_player;

typedef struct	s_process
{
	int				registry[REG_NUMBER];
	bool			carry;
	unsigned char	op;
	unsigned char	op_arg;
	unsigned char	op_clr;
	unsigned int	last_live;
	unsigned short	cycles_to_act;
	unsigned short	pc;
	unsigned short	next_set;
}				t_process;

typedef struct	s_vm
{
	unsigned char	map[MEM_SIZE];
	unsigned char	color_map[MEM_SIZE];
	short			num_of_players;
	unsigned int	num_of_proc;
	unsigned int	max_procs;
	short			cur_win_id;
	unsigned int	cycles_passed;
	unsigned int	lives_per_cycle;
	unsigned int	cycles_to_die;
	int				dump;
	t_player		**players;
	t_list			*procs;
	void			(*f_com[16])();
	char			aff;
	char			vis;
	char			s;
}				t_vm;

# define ERR_NAMES "Error: all champions shall have different numbers"
# define ERR_WRONG_NUM "Error: the number of the player shall be between 1 and "
# define USAGE "[-a] [-v] [-dump nbr_cycles] [[-n number] champion1.cor] ..."

# define A_REG 1
# define A_DIR 2
# define A_IND 3
# define A_DIR2 4
# define ERR_FLAG -1

int				read_opt(char ***av, t_vm *arena, int *id, t_player **player);
int				read_champion(char *av, t_player **player,
					int *id, t_vm *arena);

void			init_arena(t_vm *arena, t_player **players);

int				start_the_game(t_vm *arena);

int				error(char *str, char *param);
int				error2(char *str, char *param, char *str2);

int				free_players(t_player **res);
void			free_arena(t_vm *arena);

void			init_commands_array(t_vm *arena);
void			exec_command (t_vm *arena, t_process *proc);

void			wrong_argument(t_process *process);
int				cmd_get_data(void *src, int start, int len);
void			cmd_set_data(char *dst, int start, char *src, int len);
void			cmd_set_color(char *dst, int start, char color, int len);
int				cmd_get_int(t_vm *arena, t_process *proc, int src_type,
					int *shift);

void			cmd_live(t_vm *arena, t_process *proc);
void			cmd_ld(t_vm *arena, t_process *proc);
void			cmd_st(t_vm *arena, t_process *proc);
void			cmd_add(t_vm *arena, t_process *proc);
void			cmd_sub(t_vm *arena, t_process *proc);
void			cmd_and(t_vm *arena, t_process *proc);
void			cmd_or(t_vm *arena, t_process *proc);
void			cmd_xor(t_vm *arena, t_process *proc);
void			cmd_zjmp(t_vm *arena, t_process *proc);
void			cmd_ldi(t_vm *arena, t_process *proc);
void			cmd_sti(t_vm *arena, t_process *proc);
void			cmd_fork(t_vm *arena, t_process *proc);
void			cmd_lld(t_vm *arena, t_process *proc);
void			cmd_lldi(t_vm *arena, t_process *proc);
void			cmd_lfork(t_vm *arena, t_process *proc);
void			cmd_aff(t_vm *arena, t_process *proc);

void			ft_print_memory(unsigned char *mem, unsigned char *colors,
					size_t size);
void			ft_print_stat(t_vm *arena);

#endif
