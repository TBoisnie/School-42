INCLUDE_PATH=../../srcs

CONTAINERS = \
	list \
	forward_list \
	set \
	map \
	multiset \
	multimap \
	unordered_set \
	unordered_map \
	unordered_multiset \
	unordered_multimap \
	stack \
	queue \
	priority_queue \
	deque \
	vector \

OBJ_DIR=.objs
LOG_DIR=.logs

SHELL=/bin/bash
SEED := $(shell shuf -i1-100000 -n1)

USER_CONTAINERS = $(foreach a, $(CONTAINERS),ft_${a})
STD_CONTAINERS  = $(foreach a, $(CONTAINERS),std_${a})
DIFF_CONTAINERS = $(foreach a, $(CONTAINERS),diff_${a})

DEPS=$(foreach c, $(USER_CONTAINERS), ${OBJ_DIR}/$c.d)

remove_ns=$(shell echo $(1) | sed 's/[^_]*_//')

all: $(CONTAINERS)

$(USER_CONTAINERS): ${OBJ_DIR}
	@ g++ container/$(call remove_ns, $@).cpp -MMD -MF ${OBJ_DIR}/$@.d -MT $@ -DSEED=$(SEED) -DNS=ft -g3 -std=c++98 -I ${INCLUDE_PATH} -o $@

$(STD_CONTAINERS):
	@ g++ container/$(call remove_ns, $@).cpp -DSEED=$(SEED) -o $@

$(DIFF_CONTAINERS):
	@ make --no-print-directory $(call remove_ns, $@)
	@- CTN=$(call remove_ns, $@) \
	&& DIR=$(LOG_DIR)/$${CTN} \
	&& mkdir -p $${DIR} \
	&& ./ft_$${CTN} > $${DIR}/ft.log \
	&& ./std_$${CTN} > $${DIR}/std.log \
	&& diff $${DIR}/ft.log $${DIR}/std.log > $${DIR}/diff.log

.SECONDEXPANSION:

$(CONTAINERS): ft_$$(@) std_$$(@)

${OBJ_DIR}:
	mkdir $@

clean:
	@- rm -f $(DEPS)

fclean: clean
	@- rm -rf $(USER_CONTAINERS) $(STD_CONTAINERS) $(OBJ_DIR) $(LOG_DIR)

re: fclean all

diff: $(DIFF_CONTAINERS)

-include $(DEPS)
