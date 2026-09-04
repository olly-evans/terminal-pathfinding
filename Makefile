ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),)
    CLEANUP = del /F /Q
    MKDIR = mkdir
  else
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
CC_WIN := x86_64-w64-mingw32-gcc

CFLAGS := -g -O0 -Iinclude -Wall -Wextra -std=c11

# Same as CFLAGS for now but could require changes.
WIN_CFLAGS := -g -O0 -Iinclude -Wall -Wextra -std=c11
WIN_LDFLAGS := -lkernel32

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

OBJ_DIR := $(BUILD_DIR)/obj-unix
DEP_DIR := $(BUILD_DIR)/dep-unix

TARGET := $(BIN_DIR)/main.$(TARGET_EXTENSION)

SRC := $(wildcard $(SRC_DIR)/*.c)
SRC := $(filter-out $(SRC_DIR)/terminal_win32.c, $(SRC))

OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEPS := $(patsubst $(SRC_DIR)/%.c, $(DEP_DIR)/%.d, $(SRC))

OBJ_WIN := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR_WIN)/%.o, $(SRC_WIN))

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(MKDIR) -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) -p $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(CFLAGS) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

clean:
	$(CLEANUP) $(BUILD_DIR) $(BIN_DIR) build-win

run: all
	@./$(TARGET)

-include $(DEPS)

.PHONY: all clean run