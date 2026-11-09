CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -Werror -pedantic -Wvla -g

.PHONY: all run clean
all: test

test: main.c exercise.c exercise.h ../common_types.h
	$(CC) $(CFLAGS) main.c exercise.c -o test

run: test
	./test

clean:
	rm -f test *.out
