# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/19 11:09:53 by marvin            #+#    #+#              #
#    Updated: 2019/02/19 11:16:08 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

OBJ_ASM = $(patsubst *.c,*.o,$(wildcard asm/srcs/*.c))
OBJ_VM = $(patsubst *.c,*.o,$(wildcard vm/srcs/*.c))

all: $(NAME)

$(NAME): $(OBJ_VM) $(OBJ_ASM)
	make -C asm/
	make -C vm/

clean:
	make clean -C asm/
	make clean -C vm/

fclean:
	make fclean -C asm/
	make fclean -C vm/

re: fclean all

.PHONY: all clean fclean re
