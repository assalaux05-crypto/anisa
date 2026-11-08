CC = cc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -g
LDLIBS = -lsqlite3
NAME = exo
SRC = main.c sql_manual.c
OBJ = $(SRC:.c=.o)
all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)
clean:
	rm -f $(OBJ) $(NAME)
.PHONY: all clean
