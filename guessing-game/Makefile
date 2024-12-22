# Compiler
CC = gcc

# Target executable
TARGET = out

# Source files
SRC = main.c

# Object files
OBJ = $(SRC:.c=.o)

# Default Target
all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC)	$(CFLAGS) -o $(TARGET) $(OBJ)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


run: $(TARGET)
	./$(TARGET)


clean:
	rm -f $(OBJ) $(TARGET)


.PHONY: all clean
