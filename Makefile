# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 15:00:40 by abizyane          #+#    #+#              #
#    Updated: 2023/08/12 03:01:08 by ahamrad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CPPFLAGS = -I /goinfre/ahamrad/homebrew/opt/readline/include
LDFLAGS = -L /goinfre/ahamrad/homebrew/opt/readline/lib
CC = cc
CFLAGS = -Wall -Wextra -Werror -g $(CPPFLAGS) #-fsanitize=address

HEADER = minishell.h

SRC = minishell.c \
	src/tokenizer.c \
	src/tokenizer_tools.c \
	src/parse.c \
	src/ft_lst.c \
	src/ft_lst2.c \
	src/ft_lst3.c \
	src/lexical_analyzer.c \
	src/expander.c \
	src/redir.c \
	src/ft_heredoc.c \
	exec/execution.c \
	exec/execution_utils.c \
	exec/execution_utils2.c \
	exec/redirections.c \
	exec/redirections_utils.c \
	exec/env_variables.c \
	exec/signals.c \
	exec/exit_status.c \
	builtins/built_echo.c \
	builtins/built_env.c \
	builtins/built_exit.c \
	builtins/built_pwd.c \
	builtins/built_cd.c \
	builtins/built_export.c \
	builtins/built_unset.c


OBJ = $(SRC:.c=.o)

LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_HEADER = $(LIBFT_PATH)/libft.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -lreadline $(CFLAGS) $^ -o $@ -L./Libft -lft $(LDFLAGS)

$(LIBFT):
	make -C ./Libft

%.o: %.c $(HEADER) Makefile $(LIBFT_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./Libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./Libft
	rm -rf $(NAME)

x: all clean

re: fclean all