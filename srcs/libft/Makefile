# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/27 07:28:52 by tboisnie          #+#    #+#              #
#    Updated: 2020/06/02 15:30:42 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# ---------------------------------------
# Compiler
# ---------------------------------------
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# ---------------------------------------
# Files
# ---------------------------------------
INC = -I.

SRC = \
	$(wildcard array/string/*.c) \
	$(wildcard char/*.c) \
	$(wildcard io/*.c) \
	$(wildcard io/get_next_line/*.c) \
	$(wildcard list/*.c) \
	$(wildcard math/int/*.c) \
	$(wildcard memory/*.c) \
	$(wildcard string/*.c) \
	$(wildcard system/*.c) \
	$(wildcard vector/*.c) \

OBJ = $(SRC:.c=.o)

# ---------------------------------------
# Recipes
# ---------------------------------------
$(NAME): $(OBJ)
	@-echo "\033[32mLibft : Creation.\033[0m"
	@-ar rcs $@ $^

%.o: %.c
	@-echo "\033[34mLibft : Compilation. ($<)\033[0m"
	@-$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

clean:
	@-echo "\033[31mLibft : Suppression.\033[0m"
	@-rm -f $(OBJ)

fclean: clean
	@-echo "\033[31mLibft : Annihilation.\033[0m"
	@-rm -f $(NAME)

re: fclean all

bonus: all