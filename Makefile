ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
    CLEANUP = del /F /Q
    MKDIR = mkdir
  else # in a bash-like shell, like msys
    CLEANUP = rm -r
    MKDIR = mkdir -p
  endif
    TARGET_EXTENSION=exe
else
    CLEANUP = rm -r
    MKDIR = mkdir -p
    TARGET_EXTENSION=out
endif

CC := gcc
CFLAGS := -g -O0 -Iinclude -Wall -Wextra -std=c11 -MMD -MP

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

OBJ_DIR := $(BUILD_DIR)/obj
DEP_DIR := $(BUILD_DIR)/dep

TARGET := $(BIN_DIR)/main.$(TAR)

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEPS := $(patsubst $(SRC_DIR)/%.c, $(DEP_DIR)/%.d, $(SRC))

# Default goal
all: $(TARGET)

# Link all object files into the final executable
$(TARGET): $(OBJ)
	@$(MKDIR) -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c to .o and direct .d output to $(DEP_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) -p $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(CFLAGS) -MF $(DEP_DIR)/$*.d -c $< -o $@

clean:
	$(CLEANUP) $(BUILD_DIR) $(BIN_DIR)

run: all
	@./$(TARGET)

-include $(DEPS)

.PHONY: all clean run