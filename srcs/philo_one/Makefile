# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/05 22:35:46 by tboisnie          #+#    #+#              #
#    Updated: 2020/12/06 15:41:24 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
TITLE = Philosophers (philo_one)

# ---------------------------------------
# Compiler
# ---------------------------------------
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# ---------------------------------------
# Files
# ---------------------------------------
INC = -I./ \
	-I./config \
	-I./phi \
	-I./utils \
	-I./monitor

LIB = -pthread

SRC = \
	main.c \
	\
	config/clear.c \
	config/init.c \
	\
	monitor/death.c \
	\
	phi/live.c \
	phi/set_status.c \
	\
	utils/get_time_ms.c \
	utils/mem_copy.c \
	utils/min_max.c \
	utils/ret_error.c \
	utils/sleep_ms.c \
	utils/str_length.c \
	utils/str_to_int.c \
	utils/time_to_str.c \
	\

OBJ = $(SRC:.c=.o)

# ---------------------------------------
# Recipes
# ---------------------------------------
$(NAME): $(OBJ)
	@-echo "\033[32m$(TITLE) : Creation.\033[0m"
	@-$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME) $(LIB)

%.o: %.c
	@-echo "\033[34m$(TITLE) : Compilation. ($<)\033[0m"
	@-$(CC) $(CFLAGS) $(INC) -o $@ -c $<

all: $(NAME)

clean:
	@-echo "\033[31m$(TITLE) : Suppression.\033[0m"
	@-rm -f $(OBJ)

fclean: clean
	@-echo "\033[31m$(TITLE) : Annihilation.\033[0m"
	@-rm -f $(NAME)

re: fclean all
