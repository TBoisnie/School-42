# ==============================================================================
# LibFT
# ==============================================================================

# General ----------------------------------------------------------------------
TITLE := LibFT

# System -----------------------------------------------------------------------
OS_ARCH   := $(shell uname -m)
OS_KERNEL := $(shell uname -s)
OS_TYPE   := $(OS_ARCH)_$(OS_KERNEL)

# Resources --------------------------------------------------------------------
BIN_DIR := bins
INC_DIR := incs
LIB_DIR := libs
OBJ_DIR := $(BIN_DIR)/objs
SRC_DIR := srcs

EXE_EXT := .a
OBJ_EXT := .o
SRC_EXT := .c

NAME := libft

EXE         := $(BIN_DIR)/$(NAME)$(EXE_EXT)
EXE_SYMLINK := # Symbolic link (ex: EXE has a version suffix, \
                 but remove it in symlink for easy integration)

# https://www.gnu.org/software/make/manual/make.html#File-Name-Functions
# https://www.gnu.org/software/make/manual/make.html#Substitution-Refs
SRC_FILES := $(addsuffix $(SRC_EXT), \
	$(addprefix alphabetic/, \
		$(addprefix char/, \
			chr_is_type \
			chr_to_case \
		) \
		$(addprefix string/, \
			str_compare \
			str_concat \
			str_copy \
			str_duplicate \
			str_find \
			str_join \
			str_length \
			str_reverse \
			str_to_case \
			str_to_int \
			str_trim \
		) \
	) \
	$(addprefix container/, \
		$(addprefix list/, \
			lst_back \
			lst_clear \
			lst_delete \
			lst_find \
			lst_front \
			lst_index \
			lst_iterate \
			lst_map \
			lst_merge \
			lst_new \
			lst_push \
			lst_reverse \
			lst_size \
			lst_sort \
			lst_swap \
		)\
	) \
	$(addprefix io/, \
		$(addprefix get_next_line/, \
			get_next_line \
		) \
		$(addprefix put/, \
			put_format \
			put_int \
			put_str \
		) \
	) \
	$(addprefix math/, \
		math_sqrt \
	) \
	$(addprefix memory/, \
		mem_checksum \
		mem_compare \
		mem_concat \
		mem_copy \
		mem_duplicate \
		mem_fill \
		mem_hex_to_byte \
		mem_join \
		mem_reverse \
	) \
	$(addprefix numeric/, \
		$(addprefix integer/, \
			int_to_str \
		) \
	) \
	$(addprefix system/, \
		endianness \
		exit \
	) \
)

INC_FOLDERS := $(INC_DIR) $(LIB_DIR)
LIB_FOLDERS := $(LIB_DIR)

SRCS := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:$(SRC_EXT)=$(OBJ_EXT)))

INCS := $(addprefix -I, $(INC_FOLDERS))
LIBS := $(addprefix -L, $(LIB_FOLDERS))

# Compiler ---------------------------------------------------------------------
# https://www.gnu.org/software/make/manual/make.html#Implicit-Variables
AR       := ar
ARFLAGS  := rcs

CC       := gcc
CFLAGS   := -Wall -Werror -Wextra -std=gnu89 -fpic

CXX      := # C++ compiler (ex: clang++)
CXXFLAGS := # C++ compiler flags (ex: -Wall -Werror)

LDFLAGS  := $(LIBS) # Libraries flags (ex: -L. -L./libs -shared)
LDLIBS   :=         # Libraries links (ex: -lft -lmath)

MKDIR    := mkdir -p
RM       := rm -rf

# Rules ------------------------------------------------------------------------
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
$(OBJ_DIR)/%$(OBJ_EXT): $(SRC_DIR)/%$(SRC_EXT)
	@ echo "$(BLUE)$(TITLE): Compilation -> $(WHITE)$< $(RESET)"
	@ $(MKDIR) $(@D)
	@ $(CC) $(CFLAGS) $(INCS) -c $< -o $@

# Recipes ----------------------------------------------------------------------
$(NAME): all

all: libs $(OBJS)
	@ echo "$(GREEN)$(TITLE): Creation.$(RESET)"
	@ $(AR) $(ARFLAGS) $(EXE) $(OBJS)

clean: libs-clean
	@ echo "$(YELLOW)$(TITLE): Deletion.$(RESET)"
	@ $(RM) $(OBJ_DIR)

fclean: libs-fclean clean
	@ echo "$(RED)$(TITLE): Annihilation.$(RESET)"
	@ $(RM) $(BIN_DIR)

re: fclean all

# Libs -------------------------------------------------------------------------
libs:

libs-clean:

libs-fclean:

# Styles -----------------------------------------------------------------------
RED     := $(shell tput setaf 1)
GREEN   := $(shell tput setaf 2)
YELLOW  := $(shell tput setaf 3)
PINK    := $(shell tput setaf 4)
PURPLE  := $(shell tput setaf 5)
BLUE    := $(shell tput setaf 6)
WHITE   := $(shell tput setaf 7)
RESET   := $(shell tput sgr0)

# Guard ------------------------------------------------------------------------
.PHONY: $(NAME) \
	all         clean       fclean       re \
	libs   libs-clean  libs-fclean  libs-re \
	tests tests-clean tests-fclean tests-re \
