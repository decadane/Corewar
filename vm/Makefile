# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcarrot <kcarrot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/13 16:43:17 by ffahey            #+#    #+#              #
#    Updated: 2019/02/15 14:05:31 by kcarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

vpath %.c src
vpath %.h inc
vpath %.o obj

FLAGS = -Wall -Wextra -Werror

OBJ = $(addprefix obj/,$(notdir $(patsubst %.c,%.o,$(wildcard src/*.c))))

HEADERS = $(wildcard inc/*.h)

LIB = ../libft/libft.a

all: makedir make_lib $(NAME)

makedir:
	@mkdir -p obj

make_lib:
	make -C ../libft/

$(NAME): $(OBJ) $(LIB)
	gcc $(FLAGS) $^ -o $@ -Iinc -I../libft -L../libft -lft -L../libft -lftprintf

obj/%.o: %.c $(HEADERS)
	gcc $(FLAGS) -c $< -o $@ -Iinc -I../libft

clean:
	rm -rf obj/
	rm -rf ../libft/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re make_lib
