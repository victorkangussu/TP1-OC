#include <stdio.h>
#include "../ram.h"
#include "../instruction.h"
#include "../cpu.h"
#include "mul.h"

int main() {
    CPU cpu;
    RAM ram;

    initCPU(&cpu);

    printf ("O produto eh: %d\n", programaMult(&ram, &cpu, 7, 500));

    freeRAM(&ram);

    return 0;
}