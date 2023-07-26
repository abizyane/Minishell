# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 15:00:40 by abizyane          #+#    #+#              #
#    Updated: 2023/07/25 23:29:56 by ahamrad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

HEADER = minishell.h

SRC = minishell.c \
	src/tokenizer.c \
	src/tokenizer_tools.c \
	src/parse.c \
	src/ft_lst.c \
	src/lexical_analyzer.c \
	src/expander.c \
	src/redir.c \
	src/ft_heredoc.c \
	exec/execution.c \
	exec/execution_utils.c \
	exec/redirections.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./Libft
	$(CC) -lreadline $(CFLAGS) $^ -o $@ -L./Libft -lft

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./Libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./Libft
	rm -rf $(NAME)

re: fclean all

x : all clean