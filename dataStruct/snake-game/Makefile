# Makefile for Snake Game
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = snake.exe
SOURCE = snake.c

# Windows specific flags (for conio.h and windows.h)
WIN_FLAGS = 

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(WIN_FLAGS) -o $(TARGET) $(SOURCE)

clean:
	del $(TARGET) 2>nul || true

run: $(TARGET)
	.\$(TARGET)

.PHONY: all clean run