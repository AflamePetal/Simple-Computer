#ifndef INSTCODE_H
#define INSTCODE_H

#include <string.h>

// Instructions and Opcodes
#define JMP 0
#define JRP 1
#define LDN 2
#define STO 3
#define SKN 4
#define SUB 5
#define ADD 6
#define MUL 7
#define DIV 8
#define NEG 9
#define AND 10
#define OR 11
#define NOT 12
#define HLT 13

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
    if (strcmp(name, "OR") == 0) return OR;
    if (strcmp(name, "NOT") == 0) return NOT;
    if (strcmp(name, "HLT") == 0) return HLT;
    return -1; // Instruction's not found
}

#endif // INSTCODE_H