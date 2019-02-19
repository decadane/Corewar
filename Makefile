# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/19 11:09:53 by marvin            #+#    #+#              #
#    Updated: 2019/02/19 11:30:58 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

OBJ_ASM = $(patsubst *.c,*.o,$(wildcard asm/srcs/*.c))
OBJ_VM = $(patsubst *.c,*.o,$(wildcard vm/srcs/*.c))

all: $(NAME)

$(NAME): $(OBJ_VM) $(OBJ_ASM)
	make -C asm_dir/
	cp asm_dir/asm .
	make -C vm_dir/
	cp vm_dir/corewar .

clean:
	make clean -C asm_dir/
	make clean -C vm_dir/

fclean:
	make fclean -C asm_dir/
	make fclean -C vm_dir/
	rm -f corewar asm

re: fclean all

.PHONY: all clean fclean re
