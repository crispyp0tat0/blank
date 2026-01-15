# Compiler and flags
CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -Werror -g -O0 -Iinclude

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
TEST_DIR = test
TEST_BUILD_DIR = $(BUILD_DIR)/test

# Project output
TARGET = $(BUILD_DIR)/blank

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Test files
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)
TEST_TARGETS := $(patsubst $(TEST_DIR)/%.c,$(TEST_BUILD_DIR)/%,$(TEST_FILES))

# Default build (main project)
all: $(TARGET)

# Build main project executable
$(TARGET): $(OBJ_FILES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compile main project object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build test executables
tests: $(TEST_TARGETS)

# Compile each test into its own executable in build/test/
$(TEST_BUILD_DIR)/%: $(TEST_DIR)/%.c $(OBJ_FILES) | $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) $< $(OBJ_FILES) -o $@

# Directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_BUILD_DIR):
	mkdir -p $(TEST_BUILD_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean tests
