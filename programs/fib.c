#include <stdio.h>
#include "../ram.h"
#include "../instruction.h"
#include "../cpu.h"
#include "fib.h"

void programaFib(RAM *ram, CPU *cpu, int n) {
    initCPU(cpu);
    createEmptyRAM(ram, 3);

    if(n == 0) {
        printf("Resultado fibonacci: 0\n");
        return;
    }

    if(n == 1 || n == 2) {
        printf("Resultado fibonacci: 1\n");
        return;
    }

    setData(ram, 0, 0); // coloca em ram->memory[0] o número 1
    setData(ram, 1, 1); // coloca em ram->memory[1] o número 0

    for(int i = 2; i <= n; i++) { // calcula do terceiro termo até o n-ésimo termo

        Instruction soma[2]; // // cria mini-programa com 2 instruções

        soma[0].opcode = 0; // soma
        soma[0].add1 = 0; // pega memory->ram[0]
        soma[0].add2 = 1; // soma com memory->ram[1]
        soma[0].add3 = 2; // salva resultado em memory->ram[2]

        soma[1].opcode = -1; // halt

        setInstructions(cpu, soma);
        startCPU(cpu, ram);

        setData(ram, 0, getData(ram, 1)); // pega ram->memory[1] e coloca em ram->memory[0]
        setData(ram, 1, getData(ram, 2)); // pega ram->memory[2] e coloca em ram->memory[1]
    }

    cpu->register1 = getData(ram, 1); // coloca o resultado final no registrador

    printf("Resultado fibonacci: %d\n", cpu->register1);
}

//ram->memory[0] = penúltimo termo
//ram->memory[1] = último termo
//ram->memory[2] = próximo termo

int main() {
    CPU cpu;
    RAM ram;

    initCPU(&cpu);

    programaFib(&ram, &cpu, 32);

    freeRAM(&ram);

    return 0;
}