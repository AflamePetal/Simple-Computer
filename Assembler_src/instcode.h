#ifndef INSTCODE_H
#define INSTCODE_H

#include <string.h>

// Instructions and Opcodes
#define JMP 1
#define JRP 2
#define LDN 3
#define STO 4
#define SKN 5
#define SUB 6
#define ADD 7
#define MUL 8
#define DIV 9
#define NEG 10
#define AND 11
#define OR  12
#define NOT 13
#define HLT 14

int getOpcode(const char *name)
{
    if (strcmp(name, "JMP") == 0) return JMP;
    if (strcmp(name, "JRP") == 0) return JRP;
    if (strcmp(name, "LDN") == 0) return LDN;
    if (strcmp(name, "STO") == 0) return STO;
    if (strcmp(name, "SKN") == 0) return SKN;
    if (strcmp(name, "SUB") == 0) return SUB;
    if (strcmp(name, "ADD") == 0) return ADD;
    if (strcmp(name, "MUL") == 0) return MUL;
    if (strcmp(name, "DIV") == 0) return DIV;
    if (strcmp(name, "NEG") == 0) return NEG;
    if (strcmp(name, "AND") == 0) return AND;
    if (strcmp(name, "OR") == 0)  return OR;
    if (strcmp(name, "NOT") == 0) return NOT;
    if (strcmp(name, "HLT") == 0) return HLT;
    return -1; // Instruction's not found
}

#endif // INSTCODE_H