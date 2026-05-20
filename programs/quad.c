#include <stdio.h>
#include "../instruction.h"
#include "../cpu.h"
#include "../ram.h"
#include "sqrt.h"
#include "mul.h"
#include "div.h"

// [ -b +- sqrt(b^2 - 4ac) ] / 2a

void programaQuad(RAM *ram, CPU *cpu, int a, int b, int c) {

    initCPU(cpu); 
    createEmptyRAM(ram, 10);

    if (a == 0) {
        printf ("Erro. Não é função do segundo grau.\n");
        return;
    }

    int b2 = programaMult_shared(ram, cpu, b, b); // calcula b^2
    int ac = programaMult_shared(ram, cpu, a, c); // calcula a*c
    int quatroac = programaMult_shared(ram, cpu, ac, 4); // calcula 4ac

    setData(ram, 0, b2); // coloca b^2 em memory->ram[0]
    setData(ram, 1, quatroac); // coloca 4ac em memory->ram[1]

    Instruction subDelta[2]; // cria programa de sub

    subDelta[0].opcode = 1; // opcode de subtracao
    subDelta[0].add1 = 0; // memory->ram[0]
    subDelta[0].add2 = 1; // memory->ram[1]
    subDelta[0].add3 = 2; // guarda delta em memory->ram[2]

    subDelta[1].opcode = -1; // halt

    setInstructions(cpu, subDelta); // carrega sub
    startCPU(cpu, ram); // executa

    int delta = getData(ram, 2);

    if (delta < 0) {
        printf("Não existem raizes reais.\n");
        return;
    }

    int raizDelta = programaSqrt_shared(ram, cpu, delta);

    int menosB = -b;

    setData(ram, 3, menosB); // guarda -b em memory->ram[3]
    setData(ram, 4, raizDelta); // guarda sqrt(delta) em memory->ram[4]

    Instruction somaX1[2]; // calcula -b + sqrt(delta)

    somaX1[0].opcode = 0; // sum opcode
    somaX1[0].add1 = 3;
    somaX1[0].add2 = 4;
    somaX1[0].add3 = 5;

    somaX1[1].opcode = -1;

    setInstructions(cpu, somaX1);
    startCPU(cpu, ram);

    int numerador1 = getData(ram, 5);

    Instruction subX2[2]; // calcula -b - sqrt(delta)

    subX2[0].opcode = 1; // subtraction opcode
    subX2[0].add1 = 3;
    subX2[0].add2 = 4;
    subX2[0].add3 = 6;

    subX2[1].opcode = -1;

    setInstructions(cpu, subX2);
    startCPU(cpu, ram);

    int numerador2 = getData(ram, 6);

    int denominador = programaMult_shared(ram, cpu, a, 2);

    int x1 = programaDiv_shared(ram, cpu, numerador1, denominador);

    int x2 = programaDiv_shared(ram, cpu, numerador2, denominador);

    printf("X1 = %d\n", x1);

    printf("X2 = %d\n", x2);
}

int main() {
    CPU cpu;
    RAM ram;

    initCPU(&cpu);

    programaQuad(&ram, &cpu, 1, 7, 12);

    freeRAM(&ram);

    return 0;
}
