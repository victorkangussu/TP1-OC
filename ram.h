#ifndef RAM_H
#define RAM_H

typedef struct {
    int *memory;
    int size;
}RAM;

void createRAM(RAM *ram, int size);
void createEmptyRAM(RAM *ram, int size);
void createRandomRAM(RAM *ram, int size);

void setData(RAM *ram, int address, int content);
int getData(RAM *ram, int address);

void printRAM(RAM *ram);
void freeRAM(RAM *ram);

#endif