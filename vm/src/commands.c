#include "vm/inc/vm.h"

void wrong_argument ()
{
	// I don't know, what should I do here
}

int cmd_get_data (void *src, int start, int len)
{
	unsigned int result;
	int i;

	i = len;
	result = 0;
	while (i--)
		{
			result *= 256;
			result += ((unsigned char *)src)[(start + len - i) % MEM_SIZE];
		}
	return (result);
}

void	cmd_set_data(char *dst, int start, char *src, int len)
{
	int i;

	i = len;
	while (i--)
		*(dst + (start + i) % MEM_SIZE) = *src++;
}

void	cmd_set_color(char *dst, int start, char color, int len)
{
	while (len--)
		*(dst + (start + len) % MEM_SIZE) = color;
}

int		cmd_get_int(t_vm *arena, t_process *proc, int src_type, int *shift)
{
	int reg;
	int ind;

	if (src_type == A_REG)
	{
		reg = cmd_get_data(arena->map, proc->where_am_i + *shift, 1);
		if (reg <= 0 || reg > REG_NUMBER)
			return (*shift = ERR_FLAG);	//error
		*shift += 1;
		return (proc -> registry[reg-1]);
	}
	if (src_type == A_IND)
	{
		ind = cmd_get_data(arena->map, proc->where_am_i + *shift, 2) % IDX_MOD;
		*shift += 2;
		return (cmd_get_data(arena->map, (proc->where_am_i + ind) % MEM_SIZE, 4));
	}
	if (src_type == A_DIR)
	{
		*shift +=4;
		return (cmd_get_data(arena->map, (proc->where_am_i + *shift - 4) % MEM_SIZE, 4));
	}
	if (src_type == A_DIR2)
	{
		*shift +=2;
		return (cmd_get_data(arena->map, (proc->where_am_i + *shift - 2) % MEM_SIZE, 4));
	}
}

void cmd_live (t_vm *arena, t_process *proc)
{
	int value;

	value = cmd_get_data (arena->map, proc->where_am_i + 1, 4);
	proc->carry = 0; //?
	proc->where_am_i += proc->next_set;
	proc->last_live = 1; //what does it mean? last_live
	(-value > 0) && (-value <= arena->num_of_players)
	? arena->cur_win_id = (short) -value : (void) 0;
	arena->lives_per_cycle += 1; //?
}

void cmd_ld (t_vm *arena, t_process *proc)
{
	int		value;
	int		reg;
	char	is_dir;

	if (((proc->cur_op_args >> 6) == A_DIR) && (((proc->cur_op_args >> 4)
		& 0x3) == A_REG) && (!(proc->cur_op_args & 0xf)))
			is_dir = 1;
	else if (((proc->cur_op_args >> 6) == A_IND) && (((proc->cur_op_args >> 4)
		& 0x3) == A_REG) && (!(proc->cur_op_args & 0xf)))
			is_dir = 0;
	else
		return(wrong_argument ());
	value = cmd_get_data(arena->map, proc->where_am_i + (is_dir) ? 2 :
		(cmd_get_data(arena->map, proc->where_am_i + 2, 2) % IDX_MOD) , 4);
	reg = cmd_get_data(arena->map, proc->where_am_i + 4 + is_dir * 2, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return(wrong_argument());
	proc->registry[reg - 1] = value;
	proc->where_am_i = (unsigned short)((proc->where_am_i + 5 + is_dir * 2) % MEM_SIZE);
	proc->carry = !value;
}

void cmd_st (t_vm *arena, t_process *proc)
{
	int from;
	int to;
	int value;

	if (((proc->cur_op_args >> 6) != A_REG) || (((proc->cur_op_args >> 4)
		& 0x3) == A_DIR) || (!((proc->cur_op_args >> 4) & 0x3)) ||
		((proc->cur_op_args & 0xf)))
		return (wrong_argument());
	from = cmd_get_data(arena->map, proc->where_am_i + 2, 1);
	if ((from <= 0) || (from > REG_NUMBER))
		return(wrong_argument());
	if 	(((proc->cur_op_args >> 4) & 0x3) == A_REG)
	{
		to = cmd_get_data(arena->map, proc->where_am_i + 3, 1);
		if ((to <= 0) || (to > REG_NUMBER))
			return(wrong_argument());
		proc->registry[to - 1] = proc->registry[from - 1];
		proc->where_am_i = (unsigned short)((proc->where_am_i + 4) % MEM_SIZE);
	}
	else
	{
		value = cmd_get_data(arena->map, proc->where_am_i + 3, 2) % IDX_MOD;
		cmd_set_data(arena->map, (proc->where_am_i + value) % MEM_SIZE,
			(char *)(&(proc->registry[from])), 4);
		cmd_set_color(arena->color_map, (proc->where_am_i + value) % MEM_SIZE,
			arena->color_map[proc->where_am_i], 4);
		proc->where_am_i = (unsigned short)((proc->where_am_i + 5) % MEM_SIZE);
	}
}

void cmd_add (t_vm *arena, t_process *proc)
{
	int reg1;
	int reg2;
	int reg3;

	if (((proc->cur_op_args >> 6) != A_REG) ||
		(((proc->cur_op_args >> 4) & 0x3) != A_REG) ||
		(((proc->cur_op_args >> 2) & 0x3) != A_REG) ||
		((proc->cur_op_args) & 0x3))
		return (wrong_argument());
	reg1 = cmd_get_data(arena->map, proc->where_am_i+2,1);
	reg2 = cmd_get_data(arena->map, proc->where_am_i+3,1);
	reg3 = cmd_get_data(arena->map, proc->where_am_i+4,1);
	if ((reg1 <= 0) || (reg1 > REG_NUMBER) || (reg2 <= 0) ||
		(reg2 > REG_NUMBER) || (reg3 <= 0) || (reg3 > REG_NUMBER))
			return(wrong_argument());
	proc->registry[reg3 - 1] = proc->registry[reg1 - 1] + proc->registry[reg2 - 1];
	proc->carry = !(proc->registry[reg3 - 1]);
	proc->where_am_i = (unsigned short)((proc->where_am_i + 5) % MEM_SIZE);
}

void cmd_sub (t_vm *arena, t_process *proc)
{
	int reg1;
	int reg2;
	int reg3;

	if (((proc->cur_op_args >> 6) != A_REG) ||
		(((proc->cur_op_args >> 4) & 0x3) != A_REG) ||
		(((proc->cur_op_args >> 2) & 0x3) != A_REG) ||
		((proc->cur_op_args) & 0x3))
		return (wrong_argument());
	reg1 = cmd_get_data(arena->map, proc->where_am_i+2,1);
	reg2 = cmd_get_data(arena->map, proc->where_am_i+3,1);
	reg3 = cmd_get_data(arena->map, proc->where_am_i+4,1);
	if ((reg1 <= 0) || (reg1 > REG_NUMBER) || (reg2 <= 0) ||
		(reg2 > REG_NUMBER) || (reg3 <= 0) || (reg3 > REG_NUMBER))
			return(wrong_argument());
	proc->registry[reg3 - 1] = proc->registry[reg1 - 1] - proc->registry[reg2 - 1];
	proc->carry = !(proc->registry[reg3 - 1]);
	proc->where_am_i = (unsigned short)((proc->where_am_i + 5) % MEM_SIZE);

}


void cmd_and (t_vm *arena, t_process *proc)
{
	int value1;
	int value2;
	int reg;
	int shift;

	if (!(proc->cur_op_args >> 6) ||
		!((proc->cur_op_args >> 4) & 0x3) ||
		(((proc->cur_op_args >> 2) & 0x3) != A_REG) ||
		((proc->cur_op_args) & 0x3))
		return (wrong_argument());
	shift = 2;
	value1 = cmd_get_int(arena, proc, (proc->cur_op_args >> 6), &shift);
	if (shift == ERR_FLAG)
		return (wrong_argument());
	value2 = cmd_get_int(arena, proc, (proc->cur_op_args >> 4) & 0x3, &shift);
	if (shift == ERR_FLAG)
		return (wrong_argument());
	reg = cmd_get_data(arena->map, (proc->where_am_i + shift) % MEM_SIZE, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return(wrong_argument());
	proc->registry[reg - 1] = value1 & value2;
	proc->carry = !(proc->registry[reg - 1]);
	proc->where_am_i = (unsigned short)((proc->where_am_i + shift + 1) % MEM_SIZE);
}

void cmd_or (t_vm *arena, t_process *proc)
{
	int value1;
	int value2;
	int reg;
	int shift;

	if (!(proc->cur_op_args >> 6) ||
		!((proc->cur_op_args >> 4) & 0x3) ||
		(((proc->cur_op_args >> 2) & 0x3) != A_REG) ||
		((proc->cur_op_args) & 0x3))
		return (wrong_argument());
	shift = 2;
	value1 = cmd_get_int(arena, proc, (proc->cur_op_args >> 6), &shift);
	if (shift == ERR_FLAG)
		return (wrong_argument());
	value2 = cmd_get_int(arena, proc, (proc->cur_op_args >> 4) & 0x3, &shift);
	if (shift == ERR_FLAG)
		return (wrong_argument());
	reg = cmd_get_data(arena->map, (proc->where_am_i + shift) % MEM_SIZE, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return(wrong_argument());
	proc->registry[reg - 1] = value1 | value2;
	proc->carry = !(proc->registry[reg - 1]);
	proc->where_am_i = (unsigned short)((proc->where_am_i + shift + 1) % MEM_SIZE);
}

void cmd_xor (t_vm *arena, t_process *proc)
{
	int value1;
	int value2;
	int reg;
	int shift;

	if (!(proc->cur_op_args >> 6) ||
		!((proc->cur_op_args >> 4) & 0x3) ||
		(((proc->cur_op_args >> 2) & 0x3) != A_REG) ||
		((proc->cur_op_args) & 0x3))
		return (wrong_argument());
	shift = 2;
	value1 = cmd_get_int(arena, proc, (proc->cur_op_args >> 6), &shift);
	if (shift == ERR_FLAG)
		return (wrong_argument());
	value2 = cmd_get_int(arena, proc, (proc->cur_op_args >> 4) & 0x3, &shift);
	if (shift == ERR_FLAG)
		return (wrong_argument());
	reg = cmd_get_data(arena->map, (proc->where_am_i + shift) % MEM_SIZE, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return(wrong_argument());
	proc->registry[reg - 1] = value1 ^ value2;
	proc->carry = !(proc->registry[reg - 1]);
	proc->where_am_i = (unsigned short)((proc->where_am_i + shift + 1) % MEM_SIZE);
}

void cmd_zjmp (t_vm *arena, t_process *proc)
{
	int value;

	value = (cmd_get_data(arena->map, proc->where_am_i + 1, 2)) % IDX_MOD;
	if (proc->carry)
		proc->where_am_i = (proc->where_am_i + value) % MEM_SIZE;
}

void cmd_ldi (t_vm *arena, t_process *proc)
{
	int shift;
	int value;
	int reg;

	if (!(proc->cur_op_args >> 6) || !((proc->cur_op_args >> 4) & 0x3) ||
		(((proc->cur_op_args >> 4) & 0x3) == A_IND) ||
		(((proc->cur_op_args >> 2) & 0x3) != A_REG) ||
		((proc->cur_op_args) & 0x3))
		return (wrong_argument());
	shift = 2;
	value = cmd_get_int(arena, proc, (proc->cur_op_args >> 6) == A_DIR
		? A_DIR2 : (proc->cur_op_args >> 6), &shift);
	if (shift == -1)
		return (wrong_argument());
	value += cmd_get_int(arena, proc, ((proc->cur_op_args >> 4) & 0x3) == A_DIR
		? A_DIR2 : A_REG, &shift);
	if (shift == -1)
		return (wrong_argument());
	reg = cmd_get_data(arena->map, (proc->where_am_i + shift) % MEM_SIZE, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return(wrong_argument());
	proc->registry[reg-1] = cmd_get_data(arena->map,
		(proc->where_am_i + value) % IDX_MOD, 4);
	proc->where_am_i = (unsigned short)((proc->where_am_i + shift + 1) % MEM_SIZE);
}

void cmd_sti (t_vm *arena, t_process *proc)
{
	int shift;
	int value;
	int reg;

	if (((proc->cur_op_args >> 6) != A_REG) || !((proc->cur_op_args >> 4) & 0x3)
		|| !((proc->cur_op_args >> 2) & 0x3) ||
		(((proc->cur_op_args >> 2) & 0x3) == A_IND) ||
		((proc->cur_op_args) & 0x3))
		return (wrong_argument());
	shift = 3;
	reg = cmd_get_data(arena->map,proc->where_am_i + 2, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return (wrong_argument());
	value = cmd_get_int(arena, proc, (proc->cur_op_args >> 6) == A_DIR
		? A_DIR2 : (proc->cur_op_args >> 6), &shift);
	if (shift == -1)
		return (wrong_argument());
	value = (value + cmd_get_int(arena, proc, ((proc->cur_op_args >> 4) & 0x3) == A_DIR
		? A_DIR2 : A_REG, &shift)) % IDX_MOD;
	if (shift == -1)
		return (wrong_argument());
	cmd_set_data(arena->map, (proc->where_am_i + value) % MEM_SIZE,
		(char *)(&(proc->registry[reg])), 4);
	cmd_set_color(arena->color_map, (proc->where_am_i + value) % MEM_SIZE,
		arena->color_map[proc->where_am_i], 4);
	proc->where_am_i = (unsigned short)((proc->where_am_i + shift) % MEM_SIZE);
}

void	cmd_fork(t_vm *arena, t_process *proc)
{
	int value;
	t_process *new_proc;

	value = cmd_get_data(arena->map, proc->where_am_i + 1, 2) % IDX_MOD;
	new_proc = (t_process *)malloc(sizeof(t_process));
	ft_memmove(new_proc, proc, sizeof(t_process));
	new_proc->where_am_i = (new_proc->where_am_i + value) % MEM_SIZE;
	new_proc->cur_op = arena->map[new_proc->where_am_i];
	new_proc->cur_op_args = arena->map[(new_proc->where_am_i + 1) % MEM_SIZE];
	ft_lstadd(&(arena->procs), ft_lstnew(&new_proc, sizeof(t_process)));
	free(new_proc);
	arena->num_of_proc += 1;
}

void	cmd_lld(t_vm *arena, t_process *proc)
{
	int		value;
	int		reg;
	char	is_dir;

	if (((proc->cur_op_args >> 6) == A_DIR) && (((proc->cur_op_args >> 4)
		& 0x3) == A_REG) && (!(proc->cur_op_args & 0xf)))
			is_dir = 1;
	else if (((proc->cur_op_args >> 6) == A_IND) && (((proc->cur_op_args >> 4)
		& 0x3) == A_REG) && (!(proc->cur_op_args & 0xf)))
			is_dir = 0;
	else
		return(wrong_argument ());
	value = cmd_get_data(arena->map, proc->where_am_i + (is_dir) ? 2 :
		(cmd_get_data(arena->map, proc->where_am_i + 2, 2)) , 4);
	reg = cmd_get_data(arena->map, proc->where_am_i + 4 + is_dir * 2, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return(wrong_argument());
	proc->registry[reg - 1] = value;
	proc->where_am_i = (unsigned short)((proc->where_am_i + 5 + is_dir * 2) % MEM_SIZE);
	proc->carry = !value;
}

void cmd_lldi (t_vm *arena, t_process *proc)
{
	int shift;
	int value;
	int reg;

	if (!(proc->cur_op_args >> 6) || !((proc->cur_op_args >> 4) & 0x3) ||
		(((proc->cur_op_args >> 4) & 0x3) == A_IND) ||
		(((proc->cur_op_args >> 2) & 0x3) != A_REG) ||
		((proc->cur_op_args) & 0x3))
		return (wrong_argument());
	shift = 2;
	value = cmd_get_int(arena, proc, (proc->cur_op_args >> 6) == A_DIR
		? A_DIR2 : (proc->cur_op_args >> 6), &shift);
	if (shift == -1)
		return (wrong_argument());
	value += cmd_get_int(arena, proc, ((proc->cur_op_args >> 4) & 0x3) == A_DIR
		? A_DIR2 : A_REG, &shift);
	if (shift == -1)
		return (wrong_argument());
	reg = cmd_get_data(arena->map, (proc->where_am_i + shift) % MEM_SIZE, 1);
	if ((reg <= 0) || (reg > REG_NUMBER))
		return(wrong_argument());
	proc->registry[reg-1] = cmd_get_data(arena->map,
		(proc->where_am_i + value), 4);
	proc->where_am_i = (unsigned short)((proc->where_am_i + shift + 1) % MEM_SIZE);
}

void	cmd_lfork(t_vm *arena, t_process *proc)
{
	int value;
	t_process *new_proc;

	value = cmd_get_data(arena->map, proc->where_am_i + 1, 2);
	new_proc = (t_process *)malloc(sizeof(t_process));
	ft_memmove(new_proc, proc, sizeof(t_process));
	new_proc->where_am_i = (new_proc->where_am_i + value) % MEM_SIZE;
	new_proc->cur_op = arena->map[new_proc->where_am_i];
	new_proc->cur_op_args = arena->map[(new_proc->where_am_i + 1) % MEM_SIZE];
	ft_lstadd(&(arena->procs), ft_lstnew(&new_proc, sizeof(t_process)));
	free(new_proc);
	arena->num_of_proc += 1;
}

void	cmd_aff(t_vm *arena, t_process *proc)
{
	char value;
	int reg;
	int fd;

	fd = 1; //may be we have to save fd for "aff" in arena?
	if (proc->cur_op_args != 0x40)
		return (wrong_argument());
	reg = cmd_get_data(arena->map, proc->where_am_i + 2, 1);
	if (reg <= 0 || reg > REG_NUMBER)
		return (wrong_argument());
	value = (char)proc->registry[reg - 1];
	ft_putchar_fd(value, fd);
}

void exec_command (t_vm *arena, t_process *proc)
{
	if ((proc->cur_op <= 16) && (proc->cur_op >= 0))
		arena->f_com[proc->cur_op - 1] (arena, proc);
}

void	init_commands_array(t_vm *arena)
{
	arena->f_com[0] = cmd_live;
	arena->f_com[1] = cmd_ld;
	arena->f_com[2] = cmd_st;
	arena->f_com[3] = cmd_add;
	arena->f_com[4] = cmd_sub;
	arena->f_com[5] = cmd_and;
	arena->f_com[6] = cmd_or;
	arena->f_com[7] = cmd_xor;
	arena->f_com[8] = cmd_zjmp;
	arena->f_com[9] = cmd_ldi;
	arena->f_com[10] = cmd_sti;
	arena->f_com[11] = cmd_fork;
	arena->f_com[12] = cmd_lld;
	arena->f_com[13] = cmd_lldi;
	arena->f_com[14] = cmd_lfork;
	arena->f_com[15] = cmd_aff;
}

//меняет ли ldi, lldi carry?