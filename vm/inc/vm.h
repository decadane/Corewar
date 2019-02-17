/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:41:29 by kcarrot           #+#    #+#             */
/*   Updated: 2019/02/16 17:15:35 by kcarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

#include <stdbool.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include "op.h"
#include "libft.h"

#define MAGIC 0xf383ea00

typedef struct	s_player
{
	short			id;
	unsigned int	start_point;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	char			code[CHAMP_MAX_SIZE];
	unsigned int	prog_size;
}				t_player;

typedef struct	s_process
{
	int				registry[REG_NUMBER];
	bool			carry;
	unsigned char	cur_op;
	unsigned char	cur_op_args;
	unsigned int	last_live;
	unsigned short	cycles_to_act;
	unsigned short	where_am_i;
	unsigned short	next_set;
}				t_process;

typedef struct	s_vm
{
	unsigned char	map[MEM_SIZE];
	unsigned char	color_map[MEM_SIZE];
	short			num_of_players;
	unsigned int	num_of_proc;
	short			cur_win_id;
	unsigned int	cycles_passed;
	unsigned int	lives_per_cycle;
	unsigned int	cycles_to_die;
	int				dump;
	t_player		**players;
	t_list			*procs;
	void			(*f_com[16])();
}				t_vm;

#define A_REG 1
#define A_DIR 2
#define A_IND 3
#define A_DIR2 4
#define ERR_FLAG -1

int				read_opt(char **av, int *dump, int *id, t_player **player);
int				read_champion(char *av, t_player **player, int *id, int num);

void			init_arena(t_vm *arena, t_player **players, int num_of_pl, int dump);

int				start_the_game(t_vm *arena);

int				error(char *str, char *param);
int				error2(char *str, char *param, char *str2);

int				free_players(t_player **res);



#endif
