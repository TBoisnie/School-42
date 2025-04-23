# ==============================================================================
# Malloc
# ==============================================================================

# General ----------------------------------------------------------------------
TITLE := Malloc

# System -----------------------------------------------------------------------
OS_ARCH   := $(shell uname -m)
OS_KERNEL := $(shell uname -s)

ifeq ($(HOSTTYPE),)
	OS_TYPE := $(OS_ARCH)_$(OS_KERNEL)
else
	OS_TYPE := $(HOSTTYPE)
endif

# Resources --------------------------------------------------------------------
BIN_DIR := bins
INC_DIR := incs
LIB_DIR := libs
OBJ_DIR := $(BIN_DIR)/objs
SRC_DIR := srcs

EXE_EXT := .so
OBJ_EXT := .o
SRC_EXT := .c

NAME := libft_malloc

EXE         := $(BIN_DIR)/$(NAME)_$(OS_TYPE)$(EXE_EXT)
EXE_SYMLINK := $(BIN_DIR)/$(NAME)$(EXE_EXT)

# https://www.gnu.org/software/make/manual/make.html#File-Name-Functions
# https://www.gnu.org/software/make/manual/make.html#Substitution-Refs
SRC_FILES := $(addsuffix $(SRC_EXT), \
	$(addprefix _internal/, \
		$(addprefix block/, \
			_block_align_size \
			_block_create \
			_block_delete \
			_block_find_free_chunk \
		) \
		$(addprefix chunk/, \
			_chunk_allocate \
			_chunk_deallocate \
			_chunk_get_next \
			_chunk_get_prev \
			_chunk_init \
			_chunk_merge \
			_chunk_split \
		) \
		$(addprefix zone/, \
			_zone_determine_type \
			_zone_find_free_chunk \
		) \
	) \
	free \
	malloc \
	realloc \
	show_alloc_mem \
	show_alloc_mem_ex \
)

INC_FOLDERS := $(INC_DIR) $(LIB_DIR) \
	$(addprefix $(LIB_DIR)/, \
		libft/incs \
	)

LIB_FOLDERS := $(addprefix $(LIB_DIR)/, \
	libft/bins \
)

SRCS := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:$(SRC_EXT)=$(OBJ_EXT)))

INCS := $(addprefix -I, $(INC_FOLDERS))
LIBS := $(addprefix -L, $(LIB_FOLDERS))

# Compiler ---------------------------------------------------------------------
# https://www.gnu.org/software/make/manual/make.html#Implicit-Variables
AR       := # Archive compiler (ex: ar)
ARFLAGS  := # Archive flags (ex: rcs)

CC       := gcc
CFLAGS   := -Wall -Werror -Wextra -std=gnu89 -fpic

CXX      := # C++ compiler (ex: clang++)
CXXFLAGS := # C++ compiler flags (ex: -Wall -Werror -Wextra)

LDFLAGS  := $(LIBS) -shared # Linker flags (ex: -L. -L./libs -shared)
LDLIBS   := -lft -lpthread # Linker libraries (ex: -lft -lmath)

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
	@ $(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(EXE)
# @ $(CC) $(CFLAGS) $(INCS) $(LIBS) $(LDFLAGS) -o $(EXE) $(OBJS)
	@ ln -fs "$$PWD/$(EXE)" $(EXE_SYMLINK)

clean: libs-clean
	@ echo "$(YELLOW)$(TITLE): Deletion.$(RESET)"
	@ $(RM) $(OBJ_DIR)

fclean: libs-fclean clean
	@ echo "$(RED)$(TITLE): Annihilation.$(RESET)"
	@ $(RM) $(BIN_DIR)

re: fclean all

# Libs -------------------------------------------------------------------------
libs:
	@ make --no-print-directory -C $(LIB_DIR)/libft

libs-clean:
	@ make --no-print-directory -C $(LIB_DIR)/libft clean

libs-fclean:
	@ make --no-print-directory -C $(LIB_DIR)/libft fclean

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
