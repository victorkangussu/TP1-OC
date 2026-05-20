#include <stdio.h>
#include "../ram.h"
#include "../instruction.h"
#include "../cpu.h"
#include "div.h"

int main() {
    CPU cpu;
    RAM ram;

    initCPU(&cpu);

    int dividendo = 360;
    int divisor = 60;

    if (divisor == 0) {
        printf("Erro: divisor não pode ser igual a 0.\n");
    } else {
        int quociente = programaDiv(&ram, &cpu, dividendo, divisor);
        printf("Resultado da divisão: %d\n", quociente);
        freeRAM(&ram);
    }

    return 0;
}