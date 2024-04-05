# Compiler and flags
CC = cc
CFLAGS = -g -O3 -Wall -Werror -Wextra
LDFLAGS = -Lmlx -lmlx -lXext -lX11 -lm

# Source dir and files
SRC_DIR = src
SRCS = src/main.c 

# Object files
OBJ_DIR = obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_DIR)/bonus_%.o)

# Output binary
TARGET = cub3d

# Phony targets
.PHONY: all clean fclean re bonus

# Default target (all)
all: $(TARGET)

# Linking the program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Compilation rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean object files and executable
clean:
	rm -rf $(OBJ_DIR)

# Remove all generated files
fclean: clean
	rm -f $(TARGET)

# Rebuild everything
re: fclean all