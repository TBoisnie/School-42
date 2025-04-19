# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/23 07:25:16 by tboisnie          #+#    #+#              #
#    Updated: 2020/06/22 13:57:46 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc
CFLAGS = -Wall -Werror -Wextra

MLX_INC = /usr/local/include
MLX_LIB = /usr/local/lib

# 0 : MacOS, 1 : Linux
OS = 1
ifeq ($(OS), 0)
  EXT_LIB = -framework OpenGL -framework AppKit
else
  EXT_LIB = -lm -lbsd -L/usr/lib/i386-linux-gnu -lX11 -lXext
endif

INC = -I.

SRC = \
	cube3d.c \
	exit.c \
	\
	renderer/render.c \
	renderer/sky_ground.c \
	renderer/map.c \
	renderer/sprites.c \
	renderer/hud.c \
	\
	mlx_utils/darker.c \
	mlx_utils/image_get.c \
	mlx_utils/image_set.c \
	\
	parser/parse.c \
	parser/parse_definition.c \
	parser/parse_texture.c \
	parser/parse_color.c \
	parser/parse_world.c \
	parser/world_setters.c \
	parser/valid_wall.c \
	\
	exporter/export_to_bmp.c \
	exporter/export_get_header.c \
	exporter/export_get_image.c \
	\
	event/handle_key.c \
	event/handle_window.c \
	event/handle_loop.c \
	\
	list/append.c \
	list/clear.c \
	list/delete_first.c \
	list/delete_last.c \
	list/delete.c \
	list/get_last.c \
	list/new.c \
	list/prepend.c \
	list/remove_first.c \
	list/remove_last.c \
	list/remove.c \
	list/sort.c \
	list/length.c \
	\
	memory/bzero.c \
	memory/copy.c \
	memory/set.c \
	\
	math/int/min.c \
	math/int/max.c \
	\
	char/is_space.c \
	\
	string/from_int_base.c \
	string/length.c \
	string/get_next_line.c \
	string/is_space.c \
	string/str_join_char.c \
	string/str_join.c \
	string/str_to_int.c \
	string/str_contains.c \
	\
	vect/neg.c \
	vect/add.c \
	vect/sub.c \
	vect/scale.c \
	vect/rot_z.c \
	vect/dot.c \
	vect/cross.c \
	vect/length.c \
	vect/normalize.c \
	\
	color/to_int.c \
	\
	texture/load.c \
	\
	sprite/cmp.c \
	sprite/new.c \
	\
	player/move.c \
	player/rotate.c \
	player/strafe.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) $(INC) -c $< -I$(MLX_INC) -L$(MLX_LIB) -lmlx $(EXT_LIB) -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) -I$(MLX_INC) -L$(MLX_LIB) -lmlx $(EXT_LIB) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(NAME)
