CC = clang
CFLAGS = -Wall -Wextra -g
TARGET = exe

PROGRAM ?= mul_main

all:
	$(CC) $(CFLAGS) \
	programs/$(PROGRAM).c \
	programs/mul.c \
	programs/sqrt.c \
	cpu.c \
	ram.c \
	instruction.c \
	-o $(TARGET)

clean:
	rm -f $(TARGET)
	rm -rf exe.dSYM

.PHONY: all clean