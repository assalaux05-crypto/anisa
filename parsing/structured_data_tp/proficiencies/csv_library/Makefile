CC = cc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -g
LDLIBS = -lcsv
NAME = exo
SRC = main.c csv_library.c
OBJ = $(SRC:.c=.o)
all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)
clean:
	rm -f $(OBJ) $(NAME)
.PHONY: all clean
