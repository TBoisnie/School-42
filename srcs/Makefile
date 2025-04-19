# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/20 19:00:59 by tboisnie          #+#    #+#              #
#    Updated: 2019/12/04 08:53:07 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a


CC = gcc
CFLAGS = -Wall -Werror -Wextra

LIBFT_PATH = ../libs/libft/srcs/
LIBFT_NAME = libft.a

SRC = ft_printf.c \
	apply_flags.c \
	apply_precision.c \
	apply_type.c \
	apply_width.c \
	check_flags.c \
	check_length.c \
	check_precision.c \
	check_type.c \
	check_width.c \
	ft_lltoa_base.c \
	ft_ulltoa_base.c \
	int_to_struchar.c \
	ptr_to_strhex.c \
	parse.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -L. -lftprintf -o $@ -c $<

$(NAME): libft_recipe $(OBJ)
	ar rcs $(NAME) $(OBJ)

libft_recipe:
	make -C $(LIBFT_PATH) all
	cp $(LIBFT_PATH)$(LIBFT_NAME) ./$(NAME)

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJ)

fclean:
	make -C $(LIBFT_PATH) fclean
	rm -f $(OBJ)
	rm -f $(NAME)

re: fclean all
