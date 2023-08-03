# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 02:21:00 by ahamrad           #+#    #+#              #
#    Updated: 2023/07/12 03:54:55 by ahamrad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = main

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

HEADER = builtins.h

SRC = main.c \
	built_pwd.c \
	built_env.c \
	built_echo.c \
	built_cd.c \
	built_exit.c \
	built_export.c \
	built_unset.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) $^ -o $@ -L./libft -lft

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) 

re: fclean all