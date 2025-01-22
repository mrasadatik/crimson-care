# Detect platform
OS := $(shell uname -s | tr '[:upper:]' '[:lower:]')
ifeq ($(OS),linux)
	PLATFORM := linux
	RM := rm -rf
	MKDIR := mkdir -p
	EXEC_EXT := 
	EXTRA_FLAGS := 
else ifeq ($(OS),darwin)
	PLATFORM := macos
	RM := rm -rf
	MKDIR := mkdir -p
	EXEC_EXT := 
	EXTRA_FLAGS := 
else
	PLATFORM := windows
	RM := rmdir /S /Q
	MKDIR := mkdir -p
	EXEC_EXT := .exe
	EXTRA_FLAGS := -mconsole
endif

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra $(EXTRA_FLAGS)

# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
OBJ_DIR = obj
RESOURCES_DIR = resources
DB_DIR = $(RESOURCES_DIR)/db

# Source files
SRCS = main.c $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Executable names
DEBUG_EXEC = $(BIN_DIR)/Debug/CrimsonCare$(EXEC_EXT)
RELEASE_EXEC = $(BIN_DIR)/Release/CrimsonCare$(EXEC_EXT)

# Build targets
.PHONY: all clean debug release

all: debug release

debug: CFLAGS += -g3
debug: $(DEBUG_EXEC)

release: CFLAGS += -O3
release: $(RELEASE_EXEC)

$(DEBUG_EXEC): $(OBJS)
	@$(MKDIR) $(BIN_DIR)/Debug
	@$(if $(wildcard $(RESOURCES_DIR)),,$(MKDIR) $(RESOURCES_DIR))
	@$(if $(wildcard $(DB_DIR)),,$(MKDIR) $(DB_DIR))
	$(CC) $(CFLAGS) -o $@ $^

$(RELEASE_EXEC): $(OBJS)
	@$(MKDIR) $(BIN_DIR)/Release
	@$(if $(wildcard $(RESOURCES_DIR)),,$(MKDIR) $(RESOURCES_DIR))
	@$(if $(wildcard $(DB_DIR)),,$(MKDIR) $(DB_DIR))
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(if $(wildcard $(OBJ_DIR)),,$(MKDIR) $(OBJ_DIR))
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
ifeq ($(PLATFORM),windows)
	@if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR)
	@if exist $(BIN_DIR)\Debug rmdir /S /Q $(BIN_DIR)\Debug
	@if exist $(BIN_DIR)\Release rmdir /S /Q $(BIN_DIR)\Release
	@if exist $(BIN_DIR) rmdir /S /Q $(BIN_DIR)
else
	$(RM) $(OBJ_DIR) $(BIN_DIR)
endif
