#include <stdio.h>
#include "../ram.h"
#include "../instruction.h"
#include "../cpu.h"
#include "div.h"

void programaDiv(RAM *ram, CPU *cpu, int dividendo, int divisor) {

    initCPU(cpu); // inicializa a CPU (zera registradores, PC etc.)
    createEmptyRAM(ram, 3); // cria uma RAM com 3 posições zeradas

    cpu->register1 = dividendo; // coloca o dividendo no registrador 1

    Instruction trecho1[2]; // cria um mini-programa com 2 instruções

    trecho1[0].opcode = 2; // opcode 2 = copiar registrador para RAM
    trecho1[0].add1 = 1; // usar registrador 1
    trecho1[0].add2 = 0; // copiar para ram->memory[0]

    trecho1[1].opcode = -1; // halt (parar execução)

    setInstructions(cpu, trecho1); // carrega o programa na CPU
    startCPU(cpu, ram); // executa o programa

    cpu->register1 = divisor; // coloca o divisor no registrador 1

    Instruction trecho2[2]; // cria outro mini-programa

    trecho2[0].opcode = 2; // copiar registrador para RAM
    trecho2[0].add1 = 1; // usar registrador 1
    trecho2[0].add2 = 1; // copiar para ram->memory[1]

    trecho2[1].opcode = -1; // halt

    setInstructions(cpu, trecho2); // carrega o programa
    startCPU(cpu, ram); // executa

    int quociente = 0; // contador que armazenará o resultado da divisão

    while(getData(ram, 0) >= divisor) { // enquanto ram->memory[0] for maior ou igual ao divisor

        Instruction trecho3[2]; // cria programa de subtração

        trecho3[0].opcode = 1; // opcode 1 = subtração
        trecho3[0].add1 = 0; // pega ram->memory[0]
        trecho3[0].add2 = 1; // subtrai ram->memory[1]
        trecho3[0].add3 = 0; // salva resultado em rem->memory[0]

        trecho3[1].opcode = -1; // halt

        setInstructions(cpu, trecho3); // carrega o programa
        startCPU(cpu, ram); // executa a subtração

        quociente++; // conta quantas subtrações foram feitas
    }

    cpu->register1 = quociente; // coloca o resultado final no registrador 1

    printf("Resultado da divisao: %d\n", cpu->register1);
}

int main() {
    CPU cpu;
    RAM ram;

    initCPU(&cpu);

    programaDiv(&ram, &cpu, 60, -4);

    freeRAM(&ram);

    return 0;
}
