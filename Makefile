CC      := gcc
CFLAGS  := -Wall -Werror -g -Iinclude

PROJ_NAME := fuga_do_dogao

BUILD_DIR := build
OBJ_DIR   := $(BUILD_DIR)/obj
SRC_DIR   := src

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

.PHONY: all clean run

all: $(BUILD_DIR) $(OBJ_DIR) $(OBJ_FILES)
	@echo "Linkando $(BUILD_DIR)/$(PROJ_NAME)"
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/$(PROJ_NAME) $(OBJ_FILES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR): $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compilando $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: all
	@$(BUILD_DIR)/$(PROJ_NAME)
