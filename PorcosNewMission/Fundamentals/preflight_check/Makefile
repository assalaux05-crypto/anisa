CC=gcc
CFLAGS=-std=c99 -pedantic -Werror -Wall -Wextra -Wvla
NAME= ff

SRC=fibo.c hello_world.c printer.c
OBJ=$(SRC:.c=.o)
.PHONY: all clean
all:$(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)
	rm -f $(NAME)
