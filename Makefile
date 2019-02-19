# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/19 11:09:53 by marvin            #+#    #+#              #
#    Updated: 2019/02/19 11:51:20 by ffahey           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

OBJ_ASM = $(patsubst *.c,*.o,$(wildcard asm/srcs/*.c))
OBJ_VM = $(patsubst *.c,*.o,$(wildcard vm/srcs/*.c))

all: $(NAME)

$(NAME): $(OBJ_VM) $(OBJ_ASM)
	@echo -n asm: Compiling .
	@make -s -C asm_dir/
	@echo -n .
	@cp asm_dir/asm .
	@echo -n .
	@echo " \033[0;32mOK\033[0m"
	@echo -n corewar: Compiling .
	@make -s -C vm_dir/
	@echo -n .
	@cp vm_dir/corewar .
	@echo -n .
	@echo " \033[0;32mOK\033[0m"

clean:
	@make clean -s -C asm_dir/
	@make clean -s -C vm_dir/
	@echo Objects files deleted

fclean:
	@make fclean -s -C asm_dir/
	@make fclean -s -C vm_dir/
	@rm -f corewar asm
	@echo asm deleted
	@echo corvar deleted

re: fclean all

.PHONY: all clean fclean re
