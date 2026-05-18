#ifndef CPU_H
#define CPU_H
#include "instruction.h"
#include "ram.h"

typedef struct {
    int register1;
    int register2;
    int PC; // program counter
    int opcode;
    Instruction *instructions;
} CPU;

void initCPU(CPU *cpu);
void setInstructions(CPU *cpu, Instruction *instructions);
void startCPU(CPU *cpu, RAM *ram);

#endif