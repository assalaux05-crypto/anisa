CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -Wvla -g
all: test
test: main.c exercise.c exercise.h
	$(CC) $(CFLAGS) main.c exercise.c -o test
clean:
	rm -f test *.o *.tmp
.PHONY: all clean
