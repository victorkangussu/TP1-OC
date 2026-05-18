#include <stdio.h>
#include "../ram.h"
#include "../instruction.h"
#include "../cpu.h"
#include "fat.h"

void programaFat(RAM *ram, CPU *cpu, int n) {

    initCPU(cpu);
    createEmptyRAM(ram, 3);

    if(n == 0 || n == 1) { //
        printf("Resultado fatorial: 1\n");
        return;
    }

    int resultado = 1; // acumulador do fatorial

    for (int fator = 2; fator <= n; fator++) { // controla qual multiplicacao deve ser feita

        setData(ram, 0, 0); // acumulador da multiplicação, coloca 0 em ram->memory[0]
        setData(ram, 1, resultado); // coloca o valor atual em ram->memory[1]

        for(int i = 0; i < fator; i++) { // soma repetida

            Instruction soma[2];

            soma[0].opcode = 0; // soma
            soma[0].add1 = 0; // pega ram->memory[0]
            soma[0].add2 = 1; // soma com ram->memory[1]
            soma[0].add3 = 0; // salva em ram->memory[0]

            soma[1].opcode = -1; // halt

            setInstructions(cpu, soma);
            startCPU(cpu, ram);
        }

        resultado = getData(ram, 0); // atualiza resultado parcial
    }

    cpu->register1 = resultado; // coloca resultado no registrador

    printf("Resultado fatorial: %d\n", cpu->register1); // imprime
}

int main() {
    CPU cpu;
    RAM ram;

    initCPU(&cpu);

    programaFat(&ram, &cpu, 6);

    freeRAM(&ram);

    return 0;
}