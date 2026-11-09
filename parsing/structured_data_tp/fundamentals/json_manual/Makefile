CC = cc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -g
NAME = exo
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ) $(NAME)

.PHONY: all clean
