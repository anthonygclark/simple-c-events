CC := gcc
CFLAGS := -Wall -Werror -fPIC -I $(shell cd src/; pwd -P)
CPPFLAGS := 
RELEASE_FLAGS := -O2 -DNDEBUG
DEBUG_FLAGS := -ggdb

# OSX Specific Flags
ifeq ("$(shell uname)", "Darwin")
	CFLAGS += -stdlib=libstdc++
endif

NAME	:= libeventqueue
SH_NAME	:= $(NAME).so
ST_NAME	:= $(NAME).a

SOURCES	:= $(wildcard src/*.c)
OBJECTS	:= $(subst src/,obj/, $(SOURCES:.c=.o))
DEPS	:= $(OBJECTS:.o=.d)
GIT_VER	:= $(shell git describe --always)

MODE	?= DEBUG

export CC
export CFLAGS
export CPPFLAGS
export GIT_VER
export ST_NAME

.PHONY: all clean prep lib DEBUG RELEASE
.SUFFIXES:

# by default build mode and tests
all: $(MODE) tests

prep:
	@echo $(NAME) $(GIT_VER) $(MODE)
	@mkdir -p obj

RELEASE: export MODE = RELEASE 
RELEASE: export CFLAGS += $(RELEASE_FLAGS)
RELEASE: prep lib

DEBUG: export MODE = DEBUG
DEBUG: export CFLAGS += $(DEBUG_FLAGS)
DEBUG: prep lib

-include $(DEPS)

obj/%.o: src/%.c
	@echo "CC	$@"
	@$(CC) $(CFLAGS) -c -MP -MMD $< -o $@ $(CPPFLAGS)

$(ST_NAME): $(OBJECTS)
	@echo "AR	$@"
	@ar -rcs $@ $^

$(SH_NAME): $(OBJECTS)
	@echo "SO	$@"
	@$(CC) $(CFLAGS) -shared -o $@ $^ $(CPPFLAGS)

# Build both shared and static libs
lib: $(ST_NAME) $(SH_NAME)

tests: $(ST_NAME)
	@$(MAKE) --no-print-directory -C tests

static-analysis:
	@if which cppcheck > /dev/null; then \
		echo "CPPCHECK: "; cppcheck src/; \
	fi

clean:
	$(RM) -r $(BIN) obj $(ST_NAME) $(SH_NAME)
	@$(MAKE) --no-print-directory -C tests clean
