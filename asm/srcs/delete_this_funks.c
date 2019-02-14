#include <stdio.h>
#include "asm.h"

void	print_cmd(t_cmd *cmd)
{
	printf("Name: %s|\n", cmd->name);
	printf("Opcode: %d\n", cmd->opcode);
	printf("Codage: %x\n", cmd->codage);
	printf("Arg1: %s|\n", cmd->args[0]);
	printf("Arg1_type: %s|\n", cmd->args_type[0]);
	printf("Arg2: %s|\n", cmd->args[1]);
	printf("Arg2_type: %s|\n", cmd->args_type[1]);
	printf("Arg3: %s|\n", cmd->args[2]);
	printf("Arg3_type: %s|\n", cmd->args_type[2]);
	printf("Size: %d\n", cmd->cmd_size);
}

void	ft_init_cmd_array(char *arr[17])
{
	arr[0] = "live";
	arr[1] = "ld";
	arr[2] = "st";
	arr[3] = "add";
	arr[4] = "sub";
	arr[5] = "and";
	arr[6] = "or";
	arr[7] = "xor";
	arr[8] = "zjmp";
	arr[9] = "ldi";
	arr[10] = "sti";
	arr[11] = "fork";
	arr[12] = "lld";
	arr[13] = "lldi";
	arr[14] = "lfork";
	arr[15] = "aff";
	arr[16] = NULL;
}
