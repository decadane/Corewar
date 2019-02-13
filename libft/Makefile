# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffahey <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 18:30:26 by ffahey            #+#    #+#              #
#    Updated: 2019/01/30 17:21:57 by ffahey           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

SRC := $(wildcard *.c)

OBJ := $(patsubst %.c,%.o,$(SRC))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@

$(OBJ): $(SRC) libft.h
	@gcc $(CFLAGS) -c $(SRC)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
