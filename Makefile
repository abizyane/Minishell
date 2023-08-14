# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 15:00:40 by abizyane          #+#    #+#              #
#    Updated: 2023/08/14 17:28:15 by abizyane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CPPFLAGS = -I /goinfre/abizyane/homebrew/opt/readline/include
LDFLAGS = -L /goinfre/abizyane/homebrew/opt/readline/lib
CC = cc
CFLAGS = -Wall -Wextra -Werror -g $(CPPFLAGS) #-fsanitize=address

HEADER = minishell.h

SRC = minishell.c \
	src/tokenizer.c \
	src/tokenizer_tools.c \
	src/parse.c \
	src/parse2.c \
	src/ft_lst.c \
	src/ft_lst2.c \
	src/lexical_analyzer.c \
	src/expander.c \
	src/expander2.c \
	src/redir.c \
	src/ft_heredoc.c \
	exec/execution.c \
	exec/execution_utils.c \
	exec/execution_utils2.c \
	exec/exit_status.c \
	exec/redirections.c \
	exec/redirections_utils.c \
	exec/env_variables.c \
	exec/signals.c \
	builtins/built_echo.c \
	builtins/built_env.c \
	builtins/built_exit.c \
	builtins/built_pwd.c \
	builtins/built_cd.c \
	builtins/built_export.c \
	builtins/built_unset.c \
	builtins/builtins_utils.c \
	src/ft_free.c \
	src/utils.c \
	src/utils2.c


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

re: fclean all
