#include <stdio.h>
#include "../ram.h"
#include "../instruction.h"
#include "../cpu.h"
#include "mul.h"

int main() {
    CPU cpu;
    RAM ram;

    initCPU(&cpu);

    int produto = programaMult(&ram, &cpu, 10, 20);
    printf ("O produto eh: %d\n", produto);

    freeRAM(&ram);

    return 0;
}