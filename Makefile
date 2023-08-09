# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 15:00:40 by abizyane          #+#    #+#              #
#    Updated: 2023/08/09 21:24:54 by ahamrad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CPPFLAGS = -I /goinfre/ahamrad/homebrew/opt/readline/include
LDFLAGS = -L /goinfre/ahamrad/homebrew/opt/readline/lib
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address $(CPPFLAGS)

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
	exec/execution_utils2.c \
	exec/redirections.c \
	exec/env_variables.c \
	exec/signals.c \
	builtins/built_echo.c \
	builtins/built_env.c \
	builtins/built_exit.c \
	builtins/built_pwd.c \
	builtins/built_cd.c \
	builtins/built_export.c \
	builtins/built_unset.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./Libft
	$(CC) -lreadline $(CFLAGS) $^ -o $@ -L./Libft -lft $(LDFLAGS)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./Libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./Libft
	rm -rf $(NAME)

re: fclean all

x : all clean
