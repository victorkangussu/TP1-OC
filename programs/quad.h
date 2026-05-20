#ifndef QUAD_H
#define QUAD_H

// [ -b +- sqrt(b^2 - 4ac) ] / 2a

// Cases testados:

// 1) Duas raizes diferentes (Delta > 0): a = 1, b = -5, c = 6
// Solução: x1 = 3, x2 = 2

// 2) Uma raiz dupla (Delta = 0): a = 1, b = -4, c = 4
// Solução: x1 = x2 = 2

// 3) Sem raizes reais (Delta < 0): a = 1, b = 2, c = 5
// Solução: sem solução real

// 4) Raízes negativas: a = 1, b = 7, c = 12
// Solução: x1 = -3, x2 = -4

void programaQuad(RAM *ram, CPU *cpu, a, b, c);

#endif