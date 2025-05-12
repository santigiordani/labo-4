# src/utils/makefile

# Variables
SRC_DIR := $(CURDIR)
OBJ_DIR := $(SRC_DIR)/../../bin/obj/utils
SRC_FILES := $(wildcard *.c)
OBJ_FILES := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
CC := gcc
CFLAGS := -I$(SRC_DIR)/../../include/utils

.PHONY: all clean

all: $(OBJ_FILES)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "Compilando $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -f $(OBJ_DIR)/*.o
	@echo Todo limpio crack
