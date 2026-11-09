CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -Wvla -g
TARGET = test

all: $(TARGET)
$(TARGET): main.c exercise.c exercise.h
	$(CC) $(CFLAGS) main.c exercise.c -o $(TARGET)
clean:
	rm -f $(TARGET) *.o *.tmp
.PHONY: all clean
