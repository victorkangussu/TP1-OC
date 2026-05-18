CC = clang
CFLAGS = -Wall -Wextra -g
TARGET = exe

PROGRAM ?= mul

all: build

build:
	$(CC) $(CFLAGS) programs/$(PROGRAM).c cpu.c ram.c instruction.c -o $(TARGET)

clean:
	rm -f $(TARGET)
	rm -rf exe.dSYM

.PHONY: all build clean