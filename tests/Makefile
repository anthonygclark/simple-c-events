ifeq ($(ST_NAME),)
$(error This Makefile should only be called from a toplevel makefile)
endif

SOURCES := $(wildcard *.c)
BINS := $(SOURCES:.c=.exe)

all: $(BINS)

# Use static lib
%.exe: %.c
	@echo "TEST	$@"
	@$(CC) $(CFLAGS) $< ../$(ST_NAME) -o $@ $(CPPFLAGS)

clean:
	$(RM) $(BINS)
