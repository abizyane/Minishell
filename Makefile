# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 15:00:40 by abizyane          #+#    #+#              #
#    Updated: 2024/09/13 22:02:28 by abizyane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      = minishell
CC        = cc
CFLAGS    = -Wall -Wextra -Werror
RM        = rm -fr
OBJDIR    = .obj
FILES     = minishell parser/tokenizer parser/tokenizer_tools parser/parse parser/parse2 parser/ft_lst parser/ft_lst2 parser/lexical_analyzer parser/expander parser/expander2 parser/redir parser/ft_heredoc exec/execution exec/execution_utils exec/execution_utils2 exec/exit_status exec/redirections exec/redirections_utils exec/env_variables exec/signals builtins/built_echo builtins/built_env builtins/built_exit builtins/built_pwd builtins/built_cd builtins/built_export builtins/built_unset builtins/builtins_utils parser/ft_free parser/utils parser/utils2
SRC       = $(FILES:=.c)
OBJ       = $(addprefix $(OBJDIR)/, $(FILES:=.o))
INCLUDES  = minishell.h

LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_HEADER = $(LIBFT_PATH)/libft.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ -L./Libft -lft -lreadline -o $@

$(OBJDIR)/%.o: %.c $(INCLUDES) Makefile $(LIBFT_HEADER)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ./Libft

up:
	@if [ -z "`docker ps -q -f name=minishell_container`" ]; then \
        if [ -z "`docker ps -a -q -f name=minishell_container`" ]; then \
            echo "\033[0;32mInitiating startup process for Minishell ...\033[0m"; \
            docker build -t minishell:1.0.0 . && echo "\033[0;34mMinishell image built successfully.\033[0m"; \
            echo "\033[0;34mMinishell container started successfully.\033[0m"; \
            echo "\033[0;32mStartup process for Minishell completed.\033[0m"; \
            echo "\033[0;32mMinishell is now running.\033[0m"; \
            docker run -it --name minishell_container minishell:1.0.0; \
        	echo "\033[0;32mMinishell has exited.\033[0m"; \
        else \
            docker start -ai minishell_container; \
        	echo "\033[0;32mMinishell has exited.\033[0m"; \
        fi \
    else \
        echo "\033[0;33mMinishell is already running. No action required.\033[0m"; \
    fi

down:
	@if [ -n "`docker ps -aq -f name=minishell_container`" ]; then \
        echo "\033[0;31mInitiating shutdown process for Minishell ...\033[0m"; \
        docker stop minishell_container > /dev/null && echo "\033[0;34mMinishell container stopped successfully.\033[0m"; \
        docker rm minishell_container > /dev/null && echo "\033[0;34mMinishell container removed successfully.\033[0m"; \
        docker rmi minishell:1.0.0 > /dev/null && echo "\033[0;34mMinishell image removed successfully.\033[0m"; \
        echo "\033[0;31mShutdown process for Minishell completed.\033[0m"; \
    else \
        echo "\033[0;33mMinishell is not running. No action required.\033[0m"; \
    fi

dc_re: down up

clean:
	$(RM) $(OBJDIR) $(OBJ)
	make clean -C ./Libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./Libft

re: fclean all

.PHONY: all clean fclean re up down dc_re
