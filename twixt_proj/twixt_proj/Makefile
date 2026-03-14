# Compiler
CC = gcc

# Directories
SRC_DIR = src
HDR_DIR = headers
OBJ_DIR = obj

# Compiler flags (add header directory)
CFLAGS = -Wall -Wextra -I$(HDR_DIR)

# Source files
SRCS = $(SRC_DIR)/proj_main.c $(SRC_DIR)/functions.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output executable name
TARGET = twixt

# Default rule
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile each .c into .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Full rebuild
rebuild: clean all
