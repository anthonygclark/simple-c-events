
DEBUG ?= 0
COMPILE_FLAGS=-Wall -stdlib=libstdc++
DEBUG_FLAGS=-ggdb -D DEBUG=$(DEBUG)

.PHONY: all clean

all: libeventqueue.o testing.exe


testing.exe: src/test.c libeventqueue.o 
	gcc $(COMPILE_FLAGS) $(DEBUG_FLAGS) -o $@ $^

libeventqueue.o: src/events.c src/events.h
	gcc $(COMPILE_FLAGS) $(DEBUG_FLAGS) -o $@ -c $<



clean:
	@rm -rvf *.exe *.o
