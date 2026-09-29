# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Iinclude
LDFLAGS = -Llib -lporco -lhangar -lm

# Executable
TARGET = flying_machines

# Source files
SRC = src/main.c \
      src/mission.c \
      src/matching.c \
      src/simulation.c \
      src/debrief.c \
      src/mission_report.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: clean
