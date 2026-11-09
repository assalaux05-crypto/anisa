CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -Werror -pedantic -Wvla -g
JSON_CFLAGS ?=
JSON_LIBS ?=

.PHONY: all run clean
all: test

# The starter implementation does not include a JSON library yet.
# When you implement exercise.c, add your teacher's include flags to JSON_CFLAGS
# and link flags to JSON_LIBS. See ../../docs/JSON_LIBRARY_QUICK_REFERENCE.md
test: main.c exercise.c exercise.h ../common_types.h
	$(CC) $(CFLAGS) $(JSON_CFLAGS) main.c exercise.c -o test $(JSON_LIBS)

run: test
	./test

clean:
	rm -f test *.out
