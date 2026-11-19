CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror

.PHONY: clean

debug: flags.c
	$(CC) $(CFLAGS) -o $@ $^ -O0 -g
fast: flags.c
	$(CC) $(CFLAGS) -o $@ $^ -O3
small: flags.c
	$(CC) $(CFLAGS) -o $@ $^ -Oz

clean:
	$(RM) debug fast small
