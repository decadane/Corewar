# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/13 16:56:21 by marvin            #+#    #+#              #
#    Updated: 2019/02/13 18:05:29 by ffahey           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

vpath %.c srcs
vpath %.h includes
vpath %.o bin

FLAGS = -Wall -Wextra -Werror

OBJ = $(addprefix bin/,$(notdir $(patsubst %.c,%.o,$(wildcard srcs/*.c))))

HEADERS = $(wildcard includes/*.h)

LIB = ../libft/libft.a

all: makedir make_lib $(NAME)

makedir:
	@mkdir -p bin

make_lib:
	make -C ../libft/

$(NAME): $(OBJ) $(LIB)
	gcc $(FLAGS) $^ -o $@ -Iincludes -Ilibft -L../libft -lft

bin/%.o: %.c $(HEADERS)
	gcc $(FLAGS) -c $< -o $@ -Iincludes -I../libft

clean:
	rm -rf bin/
	rm -rf ../libft/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re make_lib
