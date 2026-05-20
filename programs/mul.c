#include <stdio.h>
#include "../ram.h"
#include "../instruction.h"
#include "../cpu.h"
#include "mul.h"

int programaMult(RAM *ram, CPU *cpu, int multiplicando, int multiplicador) {
    initCPU(cpu);
    createEmptyRAM(ram, 2);

    // Determina o sinal do resultado
    int sinal = 1;
    if ((multiplicando < 0 && multiplicador > 0) || (multiplicando >= 0 && multiplicador < 0)) {
        sinal = -1;
    }

    // Trabalha com valores absolutos
    int abs_multiplicando = (multiplicando < 0) ? -multiplicando : multiplicando;
    int abs_multiplicador = (multiplicador < 0) ? -multiplicador : multiplicador;

    cpu->register1 = abs_multiplicando;

    Instruction trecho1[2]; // vetor de Instruction com 2 posicoes

    trecho1[0].opcode = 2; // copiar do registrador para a ram
    trecho1[0].add1 = 1; // use o registrador 1
    trecho1[0].add2 = 1; // copie para ram posicao 1

    trecho1[1].opcode = -1; //halt

    setInstructions(cpu, trecho1); //carrega na cpu
    startCPU(cpu, ram);

    for (int i = 0; i < abs_multiplicador; i++) {
        Instruction trecho2[2];
        trecho2[0].opcode = 0; // soma
        trecho2[0].add1 = 0; // pegue ram->memory[0]
        trecho2[0].add2 = 1; // some com ram->memory[1]
        trecho2[0].add3 = 0; // salve em ram->memory[0]

        trecho2[1].opcode = -1; //halt

        setInstructions(cpu, trecho2);
        startCPU(cpu, ram);
    }

    Instruction trecho3[2];

    trecho3[0].opcode = 3; //copia da ram para o registrador
    trecho3[0].add1 = 1; //coloque no registrador 1
    trecho3[0].add2 = 0; //pegue em ram->memory[0]

    trecho3[1].opcode = -1; //halt

    setInstructions(cpu, trecho3);
    startCPU(cpu, ram);

    cpu->register1 = cpu->register1 * sinal;

    return cpu->register1;

}