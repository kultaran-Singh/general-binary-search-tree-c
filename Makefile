# Compiler
CC = gcc

# Compiler flags
# -Ilib tells gcc to look in the 'lib' folder for headers
# -Isrc tells gcc to look in the 'src' folder for headers
CFLAGS = -Wall -g -Ilib -Isrc

# All .c source files to be compiled
SRCS = main.c src/bst.c 

# The name of the final program
TARGET = bst_demo

# Default rule
all: $(TARGET)

# Rule to link the final program
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Rule to clean up
clean:
	rm -f $(TARGET)