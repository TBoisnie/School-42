# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/27 05:27:37 by tboisnie          #+#    #+#              #
#    Updated: 2020/06/02 16:41:12 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# ---------------------------------------
# Compiler
# ---------------------------------------
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# ---------------------------------------
# Files
# ---------------------------------------
INC = -I./ \

LIB = -L./libft -lft

SRC = \
	minishell.c \
	\
	$(wildcard builtin/*.c) \
	$(wildcard command/*.c) \
	$(wildcard environnement/*.c) \
	$(wildcard execute/*.c) \
	$(wildcard get_input/*.c) \
	$(wildcard parser/*.c) \
	$(wildcard separator/*.c) \
	$(wildcard signal/*.c) \
	\

OBJ = $(SRC:.c=.o)

# ---------------------------------------
# Recipes
# ---------------------------------------
$(NAME): ft $(OBJ)
	@-echo "\033[32mMiniShell : Creation.\033[0m"
	@-$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME) $(LIB)

%.o: %.c
	@-echo "\033[34mMiniShell : Compilation. ($<)\033[0m"
	@-$(CC) $(CFLAGS) $(INC) -o $@ -c $<

all: ft $(NAME)

clean:
	@-echo "\033[31mMiniShell : Suppression.\033[0m"
	@-make -s -C libft clean
	@-rm -f $(OBJ)

fclean: clean
	@-echo "\033[31mMiniShell : Annihilation.\033[0m"
	@-make -s -C libft fclean
	@-rm -f $(NAME)

re: fclean all

bonus: all

ft:
	@-make -s -C libft all
