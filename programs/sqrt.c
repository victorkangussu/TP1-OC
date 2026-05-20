#include <stdio.h>
#include "../ram.h"
#include "../instruction.h"
#include "../cpu.h"
#include "sqrt.h"
#include "mul.h"

int programaSqrt(RAM *ram, CPU *cpu, int n) {

    initCPU(cpu);
    createEmptyRAM(ram, 2);

    if (n < 0) return -1; //numeros negativos nao possuem raiz quadrada real
    
    int candidato = 0;

    while (1) {
        cpu->register1 = programaMult(ram, cpu, candidato, candidato);
        cpu->register2 = candidato;

        if (cpu->register1 == n) return cpu->register2;
        if (cpu->register1 > n) break;
        candidato++;
    }

    return -2; //nao possui raiz quadrada inteira
}




