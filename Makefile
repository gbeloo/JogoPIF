# Makefile para WSL/Ubuntu

# Compilador e flags
CC      := gcc
CFLAGS  := -Wall -Wextra -g3 -Icli-lib/include

# Fontes
SRCS    := src/game.c \
           src/main.c \
           cli-lib/src/keyboard.c \
           cli-lib/src/screen.c \
           cli-lib/src/timer.c

# Nome do executável
TARGET  := bin/game

# Converte cada .c em .o
OBJS    := $(SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

# Linkagem final
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@

# Regra genérica de compilação de .c para .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa todos os .o e o executável
clean:
	rm -rf $(OBJS) $(TARGET)

# Para rodar o jogo imediatamente
run: all
	./$(TARGET)
