# ==============================================================================
# FtSSL
# ==============================================================================

# General ----------------------------------------------------------------------
TITLE := FtSSL

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

EXE_EXT :=
OBJ_EXT := .o
SRC_EXT := .c

NAME := ft_ssl

EXE         := $(BIN_DIR)/$(NAME)$(EXE_EXT)
EXE_SYMLINK :=

# https://www.gnu.org/software/make/manual/make.html#File-Name-Functions
# https://www.gnu.org/software/make/manual/make.html#Substitution-Refs
LIB_FILES := $(addsuffix $(SRC_EXT), \
)
SRC_FILES := $(addsuffix $(SRC_EXT), \
	$(addprefix algorithms/, \
		$(addprefix message-digest/, \
			md5 \
			sha256 \
			whirlpool \
		) \
	) \
	$(addprefix commands/, \
		hash \
	) \
	ft_ssl \
)

INC_FOLDERS := $(INC_DIR) $(LIB_DIR)
LIB_FOLDERS := $(addprefix $(LIB_DIR)/, \
	libft/bins \
)

SRCS := $(addprefix $(SRC_DIR)/, $(SRC_FILES)) \
        $(addprefix $(LIB_DIR)/, $(LIB_FILES))
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:$(SRC_EXT)=$(OBJ_EXT))) \

INCS := $(addprefix -I, $(INC_FOLDERS))
LIBS := $(addprefix -L, $(LIB_FOLDERS))

# Compiler ---------------------------------------------------------------------
# https://www.gnu.org/software/make/manual/make.html#Implicit-Variables
AR       := # Archive compiler (ex: ar)
ARFLAGS  := # Archive flags (ex: rcs)

CC       := gcc # C compiler (ex: gcc)
CFLAGS   := -Wall -Werror -Wextra # Compiler flags (ex: -Wall -Werror -Wextra)

CXX      := # C++ compiler (ex: g++)
CXXFLAGS := # C++ compiler flags (ex: -Wall -Werror -Wextra)

LDFLAGS  := $(LIBS) # Linker flags (ex: -L. -L./libs -shared)
LDLIBS   := -lft # Linker libraries (ex: -lft -lmath)

MKDIR    := mkdir -p
RM       := rm -rf

# Rules ------------------------------------------------------------------------
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
$(OBJ_DIR)/%$(OBJ_EXT): %$(SRC_EXT)
	@ echo "$(BLUE)$(TITLE): Compilation -> $(WHITE)$< $(RESET)"
	@ $(MKDIR) $(@D)
	@ $(CC) $(CCFLAGS) $(INCS) -c $< -o $@

# Recipes ----------------------------------------------------------------------
$(NAME): all

all: libs $(OBJS)
	@ echo "$(GREEN)$(TITLE): Creation.$(RESET)"
	@ $(CC) $(CCFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(EXE)
# @ $(CC) $(CCFLAGS) $(LIBS) $(LDFLAGS) -o $(EXE) $(OBJS)
# @ ln -fs "$$PWD/$(EXE)" $(EXE_SYMLINK)

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
	all       clean      fclean      re \
	libs libs-clean libs-fclean libs-re \
