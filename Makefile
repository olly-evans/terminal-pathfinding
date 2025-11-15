CC := gcc
CFLAGS := -g -O0 -Iinclude -Wall -Wextra -std=c11 -MMD -MP

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

TARGET := $(BIN_DIR)/main

SRC := $(wildcard $(SRC_DIR)/*.c) # Pattern for .c
OBJ := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC)) # Substitute this pattern for objects
DEPS := $(OBJ:.o=.d)

# Default goal
all: $(TARGET)

# Link all object files into the final executable
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c file into a .o object file, generating dependency files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

run: all
	@echo "Running $(TARGET)..."
	@./$(TARGET)

-include $(DEPS)

.PHONY: all clean run