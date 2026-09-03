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

WIN_CFLAGS := -g -O0 -Iinclude -Wall -Wextra -std=c11
WIN_LDFLAGS := -lkernel32

SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

OBJ_DIR := $(BUILD_DIR)/obj-unix
DEP_DIR := $(BUILD_DIR)/dep-unix

OBJ_DIR_WIN := $(BUILD_DIR)/obj-win
DEP_DIR_WIN := $(BUILD_DIR)/dep-win

TARGET := $(BIN_DIR)/main.$(TARGET_EXTENSION)
TARGET_WIN := $(BIN_DIR)/main.exe

SRC := $(wildcard $(SRC_DIR)/*.c)
SRC := $(filter-out $(SRC_DIR)/terminal_win32.c, $(SRC))
SRC_WIN := $(filter-out $(SRC_DIR)/terminal_unix.c, $(wildcard $(SRC_DIR)/*.c))

OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEPS := $(patsubst $(SRC_DIR)/%.c, $(DEP_DIR)/%.d, $(SRC))

OBJ_WIN := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR_WIN)/%.o, $(SRC_WIN))
DEPS_WIN := $(patsubst $(SRC_DIR)/%.c, $(DEP_DIR_WIN)/%.d, $(SRC_WIN))

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(MKDIR) -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) -p $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(CFLAGS) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

clean:
	$(CLEANUP) $(BUILD_DIR) $(BIN_DIR)

run: all
	@./$(TARGET)

################ WINDOWS #################

windows: $(TARGET_WIN)

$(TARGET_WIN): $(OBJ_WIN)
	@$(MKDIR) -p $(BIN_DIR)
	$(CC_WIN) $(WIN_CFLAGS) -o $@ $^ $(WIN_LDFLAGS)

$(OBJ_DIR_WIN)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) -p $(OBJ_DIR_WIN) $(DEP_DIR_WIN)
	$(CC_WIN) $(WIN_CFLAGS) -MMD -MP -MF $(DEP_DIR_WIN)/$*.d -c $< -o $@

-include $(DEPS)
-include $(DEPS_WIN)

.PHONY: all clean run windows