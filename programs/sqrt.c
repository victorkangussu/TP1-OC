#include <stdio.h>
#include "../ram.h"
#include "../instruction.h"
#include "../cpu.h"
#include "sqrt.h"
#include "mul.h"

void programaSqrt(RAM *ram, CPU *cpu, int n) {

    initCPU(cpu);
    createEmptyRAM(ram, 2);

    if (n < 0) {
        printf("Número negativo não possui raiz quadrada real.\n");
        return;
    }

    int candidato = 0;

    while (1) {

        cpu->register1 = programaMult(ram, cpu, candidato, candidato);
        cpu->register2 = candidato;

        if (cpu->register1 == n) {
            printf ("Raiz quadrada de %d eh: %d\n", n, cpu->register2);
            return;
        }

        if (cpu->register1 > n) break;

        candidato++;

    }
    printf("%d não possui raiz quadrada inteira.\n", n);
}

int main() {
    CPU cpu;
    RAM ram;

    initCPU(&cpu);

    programaSqrt(&ram, &cpu, 160000);

    freeRAM(&ram);

    return 0;
}


