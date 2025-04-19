# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/29 21:46:32 by tboisnie          #+#    #+#              #
#    Updated: 2020/12/08 01:59:00 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = replace
TITLE = CPP - Day 1 (ex07)

# ---------------------------------------
# Colors
# ---------------------------------------
COLOR_RED   = \e[91m
COLOR_GREEN = \e[92m
COLOR_BLUE  = \e[94m
COLOR_NONE  = \e[0m

# ---------------------------------------
# Compiler
# ---------------------------------------
CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# ---------------------------------------
# Files
# ---------------------------------------
INC = -I./ \

LIB = \

SRC = \
	main.cpp \
	\

OBJ = $(SRC:.cpp=.o)

# ---------------------------------------
# Recipes
# ---------------------------------------
$(NAME): $(OBJ)
	@-echo "$(COLOR_GREEN)$(TITLE) : Creation.$(COLOR_NONE)"
	@-$(CXX) $(CXXFLAGS) $(INC) $(OBJ) -o $(NAME) $(LIB)

%.o: %.cpp
	@-echo "$(COLOR_BLUE)$(TITLE) : Compilation. ($<)$(COLOR_NONE)"
	@-$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

all: $(NAME)

clean:
	@-echo "$(COLOR_RED)$(TITLE) : Suppression.$(COLOR_NONE)"
	@-rm -f $(OBJ)

fclean: clean
	@-echo "$(COLOR_RED)$(TITLE) : Annihilation.$(COLOR_NONE)"
	@-rm -f $(NAME)

re: fclean all
