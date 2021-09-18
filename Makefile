# Autora: Ana Clara Loureiro Cruz
# Data: 17-09-2021

#  TRABALHO 2 - SISTEMAS OPERACIONAIS

# Compilador
CC = gcc

# Flags:
CFLAGS  = -Wall -Werror -D_POSIX_THREAD_SEMANTICS
LDFLAGS = -pthread

TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LDFLAGS)

clean:
	$(RM) $(TARGET)