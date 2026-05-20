#include <stdio.h>
#include "../ram.h"
#include "../instruction.h"
#include "../cpu.h"
#include "mul.h"
#include "sqrt.h"

int main() {
    CPU cpu;
    RAM ram;

    initCPU(&cpu);

    int raiz = programaSqrt(&ram, &cpu, 1000);
    if (raiz != -1 && raiz != -2) printf("Raiz quadrada eh: %d\n", raiz);
    else if (raiz == -1) printf ("Não possui raiz quadrada real.\n");
    else printf ("Não possui raiz quadrada inteira.\n");

    freeRAM(&ram);

    return 0;
}