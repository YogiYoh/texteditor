# Use Cygwin's gcc compiler
CC = gcc

# Compiler flags: Wall enables all warnings, g adds debugging symbols, and extra warnings
CFLAGS = -Wall -Wextra -g

# Define the output executable
TARGET = kilo.exe

# Define the source files
SRC = kilo.c

# Build target
all: $(TARGET)

# Build rule for the target
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean rule to remove the executable
clean:
	rm -f $(TARGET)
