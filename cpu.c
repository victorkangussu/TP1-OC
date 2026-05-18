#include <stdio.h>
#include "cpu.h"
#include "ram.h"

void initCPU(CPU *cpu) {
    cpu->register1 = 0;
    cpu->register2 = 0;
    cpu->PC = 0;
    cpu->opcode = 0;
    cpu->instructions = NULL;
}

void setInstructions(CPU *cpu, Instruction *instructions) {
    cpu->instructions = instructions;
}

void startCPU(CPU *cpu, RAM *ram) {
    cpu->opcode = 0;
    cpu->PC = 0;
    while (cpu->opcode != -1) {
        Instruction inst = cpu->instructions[cpu->PC];
        cpu->opcode = inst.opcode;
        switch (cpu->opcode) {
            case -1: //HALT
                //printf("Program finished!\n");
                //printRAM(ram);
                break;

            case 0: //ADD
                cpu->register1 = getData(ram, inst.add1);
                cpu->register2 = getData(ram, inst.add2);

                cpu->register1 += cpu->register2;

                setData(ram, inst.add3, cpu->register1);

                //printf("Inst sum -> RAM position %d with content %d\n", inst.add3, cpu->register1);
                break;  

            case 1: //SUBTRACT
                cpu->register1 = getData(ram, inst.add1);
                cpu->register2 = getData(ram, inst.add2);

                cpu->register1 -= cpu->register2;

                setData(ram, inst.add3, cpu->register1);

                //printf("Inst sub -> RAM position %d with content %d\n", inst.add3, cpu->register1);
                break;  

            case 2: //copies register to ram
                if (inst.add1 == 1) { // a instrucao manda usar o registrador 1
                    setData(ram, inst.add2, cpu->register1);
                    //printf("Inst copy_reg_ram -> RAM position %d with content %d\n", inst.add2, cpu->register1);
                } 
                
                else if (inst.add1 == 2) {
                    setData(ram, inst.add2, cpu->register2);
                    //printf("Inst copy_reg_ram -> RAM position %d with content %d\n", inst.add2, cpu->register2);
                }
                break;

            case 3: //copies ram to register
                if (inst.add1 == 1) { 
                    cpu->register1 = getData(ram, inst.add2);
                    //printf("Inst copy_ram_reg -> Register1 with content %d\n", cpu->register1);
                } 

                else if (inst.add1 == 2) {
                    cpu->register2 = getData(ram, inst.add2);
                    //printf("Inst copy_ram_reg -> Register2 with content %d\n", cpu->register2);
                }
                break;
        }
        cpu->PC++;
    }
}