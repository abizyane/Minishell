# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 11:33:24 by abizyane          #+#    #+#              #
#    Updated: 2023/06/20 20:57:17 by abizyane         ###   ########.fr        #
=======
#    By: abizyane <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 11:33:24 by abizyane          #+#    #+#              #
#    Updated: 2022/10/28 11:01:44 by abizyane         ###   ########.fr        #
>>>>>>> ...
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC =  ft_bzero.c ft_isascii.c ft_memcpy.c  ft_strchr.c  ft_strlen.c\
			ft_isalnum.c ft_isdigit.c ft_memmove.c ft_strlcat.c ft_tolower.c\
            ft_isalpha.c ft_isprint.c ft_memset.c  ft_strlcpy.c ft_toupper.c\
            ft_strrchr.c ft_memchr.c ft_atoi.c ft_strncmp.c ft_memcmp.c\
			ft_strnstr.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c\
			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\

OBJ = $(SRC:.c=.o)
RM = rm -rf
NAME  = libft.a
HEADER = libft.h

all : $(NAME)

$(NAME) : $(OBJ)
<<<<<<< HEAD
	@ar -rc $(NAME) $(OBJ)

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)
=======
	ar -rc $(NAME) $(OBJ)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)
>>>>>>> ...

re : fclean all

.PHONY: all fclean clean re
