
CC = gcc
CPPFLAGS = $(shell sdl2-config --cflags)
CFLAGS = -Wall -Wextra -Wvla -Werror -std=c99 -pedantic
LDLIBS = $(shell sdl2-config --libs)

SRCS = game.c render.c main.c
OBJS = $(SRCS:.c=.o)
TARGET = tic_tac_toe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o $(TARGET)

clean:
	$(RM) $(TARGET)
	$(RM) $(OBJS)

.PHONY: all clean