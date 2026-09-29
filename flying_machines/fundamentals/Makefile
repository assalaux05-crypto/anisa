# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Iinclude
LDFLAGS = -Llib -lporco -lm

# Executable
TARGET = flying_machines

# Source files
SRC = src/main.c \
      src/warmup.c \
      src/records.c \
      src/physics.c \
      src/report.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: clean
