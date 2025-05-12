# makefile en el directorio raíz

CC := gcc
CFLAGS := -Iinclude -Iinclude/utils
LDFLAGS := -lm

# Rutas
SRC_DIR := src
UTILS_DIR := $(SRC_DIR)/utils
BIN_DIR := bin
OBJ_DIR := $(BIN_DIR)/obj
UTILS_OBJ_DIR := $(OBJ_DIR)/utils

TARGET := $(BIN_DIR)/main

# Archivos fuente y objeto
SRC_FILES := $(SRC_DIR)/main.c $(wildcard $(UTILS_DIR)/*.c)
OBJ_FILES := $(OBJ_DIR)/main.o $(patsubst $(UTILS_DIR)/%.c,$(UTILS_OBJ_DIR)/%.o,$(wildcard $(UTILS_DIR)/*.c))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@echo "Enlazando ejecutable: $@"
	@$(CC) $^ -o $@ $(LDFLAGS)

# Compilación de main.c
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c | $(OBJ_DIR)
	@echo "Compilando $< -> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilación de utils/*.c
$(UTILS_OBJ_DIR)/%.o: $(UTILS_DIR)/%.c | $(UTILS_OBJ_DIR)
	@echo "Compilando $< -> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# Crear carpetas necesarias
$(OBJ_DIR):
	@mkdir -p $@

$(UTILS_OBJ_DIR):
	@mkdir -p $@

clean:
	@echo "Limpiando objetos y ejecutable"
	@rm -f $(OBJ_DIR)/main.o $(UTILS_OBJ_DIR)/*.o $(TARGET)

run:
	@./bin/main

plot:
	@gnuplot scripts/a.gnuplot
	@gnuplot scripts/b.gnuplot
	@gnuplot scripts/c.gnuplot