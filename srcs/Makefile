# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/16 22:25:12 by tboisnie          #+#    #+#              #
#    Updated: 2020/06/26 17:02:07 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ASM
NAME = libasm.a

NASM = nasm

# 0 : MacOS, 1 : Linux
OS = 1
ifeq ($(OS), 0)
  NFLAGS = --no-line -f macho64
else
  NFLAGS = --no-line -felf64
endif

# CC (test)
NAME_TEST = test

CC = gcc
CFLAGS = -Wall -Wextra -Werror -no-pie

# ASM files
NSRC = \
	io/ft_read.s \
	io/ft_write.s \
	\
	string/ft_strcmp.s \
	string/ft_strcpy.s \
	string/ft_strdup.s \
	string/ft_strlen.s \

NOBJ = $(NSRC:.s=.o)

# C files (test)
CSRC = \
	../tests/main.c \

COBJ = $(CSRC:.c=.o)

# Recipes
all: $(NAME)

%.o: %.s
	$(NASM) $(NFLAGS) $< -o $@

$(NAME): $(NOBJ)
	ar rcs $@ $^

test: $(NAME) $(COBJ)
	$(CC) $(CFLAGS) $(CSRC) -L. -lasm -o $(NAME_TEST)

clean:
	rm -rf $(NOBJ)
	rm -rf $(COBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_TEST)
	rm -rf test.output

re: fclean all
