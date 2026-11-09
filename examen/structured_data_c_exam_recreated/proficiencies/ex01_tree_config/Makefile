CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror -Wvla -g
LDLIBS = -lyajl
TARGET = test
all: $(TARGET)
$(TARGET): main.c exercise.c exercise.h
	$(CC) $(CFLAGS) main.c exercise.c -o $(TARGET) $(LDLIBS)
clean:
	rm -f $(TARGET) *.o *.tmp *.json.out
.PHONY: all clean
