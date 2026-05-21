#include <stdio.h>
#include "../ram.h"
#include "../instruction.h"
#include "../cpu.h"
#include "div.h"
#include "mul.h"

int programaDiv(RAM *ram, CPU *cpu, int dividendo, int divisor) {
    initCPU(cpu);
    createEmptyRAM(ram, 3);

    if (divisor == 0) {
        printf("Erro: divisor não pode ser igual a 0.\n");
        return -1; // erro: divisão por zero
    }

    // Determina o sinal do resultado
    int sinal = 1;
    if ((dividendo < 0 && divisor > 0) || (dividendo >= 0 && divisor < 0)) {
        sinal = -1;
    }

    // Trabalha com valores absolutos
    int abs_dividendo = (dividendo < 0) ? -dividendo : dividendo;
    int abs_divisor = (divisor < 0) ? -divisor : divisor;

    cpu->register1 = abs_dividendo; // coloca o dividendo no registrador 1

    Instruction trecho1[2]; // cria um mini-programa com 2 instruções

    trecho1[0].opcode = 2; // opcode 2 = copiar registrador para RAM
    trecho1[0].add1 = 1; // usar registrador 1
    trecho1[0].add2 = 0; // copiar para ram->memory[0]

    trecho1[1].opcode = -1; // halt (parar execução)

    setInstructions(cpu, trecho1); // carrega o programa na CPU
    startCPU(cpu, ram); // executa o programa

    cpu->register1 = abs_divisor; // coloca o divisor no registrador 1

    Instruction trecho2[2]; // cria outro mini-programa

    trecho2[0].opcode = 2; // copiar registrador para RAM
    trecho2[0].add1 = 1; // usar registrador 1
    trecho2[0].add2 = 1; // copiar para ram->memory[1]

    trecho2[1].opcode = -1; // halt

    setInstructions(cpu, trecho2); // carrega o programa
    startCPU(cpu, ram); // executa

    int quociente = 0; // contador que armazenará o resultado da divisão

    while(getData(ram, 0) >= abs_divisor) { // enquanto ram->memory[0] for maior ou igual ao divisor

        Instruction trecho3[2]; // cria programa de subtração

        trecho3[0].opcode = 1; // opcode 1 = subtração
        trecho3[0].add1 = 0; // pega ram->memory[0]
        trecho3[0].add2 = 1; // subtrai ram->memory[1]
        trecho3[0].add3 = 0; // salva resultado em ram->memory[0]

        trecho3[1].opcode = -1; // halt

        setInstructions(cpu, trecho3); // carrega o programa
        startCPU(cpu, ram); // executa a subtração

        quociente++; // conta quantas subtrações foram feitas
    }

    cpu->register1 = quociente * sinal; // coloca o resultado final com sinal correto no registrador 1

    return (cpu->register1);
}

// Versao compartilhada sem createEmptyRAM() para uso em quad.c
int programaDiv_shared(RAM *ram, CPU *cpu, int dividendo, int divisor) {
    initCPU(cpu);

    if (divisor == 0) {
        printf("Erro: divisor não pode ser igual a 0.\n");
        return -1; // erro: divisão por zero
    }

    // Determina o sinal do resultado
    int sinal = 1;
    if ((dividendo < 0 && divisor > 0) || (dividendo >= 0 && divisor < 0)) {
        sinal = -1;
    }

    // Trabalha com valores absolutos
    int abs_dividendo = (dividendo < 0) ? -dividendo : dividendo;
    int abs_divisor = (divisor < 0) ? -divisor : divisor;

    cpu->register1 = abs_dividendo; // coloca o dividendo no registrador 1

    setData(ram, 0, abs_dividendo); // coloca dividendo em ram->memory[0]
    setData(ram, 1, abs_divisor);   // coloca divisor em ram->memory[1]

    int quociente = 0; // contador que armazenará o resultado da divisão

    while(getData(ram, 0) >= abs_divisor) { // enquanto ram->memory[0] for maior ou igual ao divisor

        Instruction trecho3[2]; // cria programa de subtração

        trecho3[0].opcode = 1; // opcode 1 = subtração
        trecho3[0].add1 = 0; // pega ram->memory[0]
        trecho3[0].add2 = 1; // subtrai ram->memory[1]
        trecho3[0].add3 = 0; // salva resultado em ram->memory[0]

        trecho3[1].opcode = -1; // halt

        setInstructions(cpu, trecho3); // carrega o programa
        startCPU(cpu, ram); // executa a subtração

        quociente++; // conta quantas subtrações foram feitas
    }

    cpu->register1 = quociente * sinal; // coloca o resultado final com sinal correto no registrador 1

    return (cpu->register1);
}
