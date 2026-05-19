#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "ram.h"

void createRAM(RAM *ram, int size) {
    ram->memory = malloc(size * sizeof(int));
    ram->size = size;
}

void createEmptyRAM(RAM *ram, int size) {
    createRAM(ram, size);
    for (int i = 0; i < size; i++)
        ram->memory[i] = 0;
}

void createRandomRAM(RAM *ram, int size) {
    srand(time(NULL));
    createRAM(ram, size);
    for (int i = 0; i < size; i++)
        ram->memory[i] = rand();
}

//coloca dado do registrador, na ram
void setData(RAM *ram, int address, int content) {
    if (address >= 0 && address < ram->size)
        ram->memory[address] = content;
}

//pega dado da ram
int getData(RAM *ram, int address) {
    if (address < 0 || address >= ram->size) {
        printf("Invalid memory access: %d\n", address);
        return 0;
    }
    return ram->memory[address];
}

void printRAM(RAM *ram) {
    printf("RAM contains: \n");
    for (int i = 0; i < ram->size; i++)
        printf("%d\n", ram->memory[i]);
}

void freeRAM(RAM *ram) {
    free (ram->memory);
}
