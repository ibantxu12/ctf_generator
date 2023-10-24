# Nombre del ejecutable
TARGET = ctf-generator

# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -Wall -Wextra

# Opciones de depuración
DEBUG_CFLAGS = -g

# Archivos fuente
SRCS = src/main.c src/herramientas.c src/argumentos.c src/maquina.c src/vulnerabilidades.c

# Directorio para archivos objeto
OBJ_DIR = obj

# Archivos objeto generados a partir de los archivos fuente
OBJS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Regla para la compilación del programa sin depuración
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regla para la generación de archivos objeto desde archivos fuente
$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean debug

# Regla para limpiar archivos generados
clean:
	rm -f $(TARGET) $(OBJS)

# Regla para compilar en modo depuración
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: clean $(TARGET)
