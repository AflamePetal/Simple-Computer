#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instcode.h"

#define CHUNK_SIZE 256

#define FOR_LOGISIM 1 // Set this to '1' if you want the output to use in logisim.

// This snippet is for printing an integer in its binary form
#define _8_BIT_PATTERN "%c%c%c%c%c%c%c%c"
#define INT_TO_BINARY(byte)          \
    ((byte) & 0x80 ? '1' : '0'),     \
        ((byte) & 0x40 ? '1' : '0'), \
        ((byte) & 0x20 ? '1' : '0'), \
        ((byte) & 0x10 ? '1' : '0'), \
        ((byte) & 0x08 ? '1' : '0'), \
        ((byte) & 0x04 ? '1' : '0'), \
        ((byte) & 0x02 ? '1' : '0'), \
        ((byte) & 0x01 ? '1' : '0')

void output(int num, FILE *txtFile)
{
    int num16 = num >> 16;
    if (FOR_LOGISIM)
    {
        fprintf(txtFile, "%01x\n", num);
    }
    else
    {
        fprintf(txtFile, ""_8_BIT_PATTERN""_8_BIT_PATTERN""_8_BIT_PATTERN""_8_BIT_PATTERN"\n",
            INT_TO_BINARY(num16 >> 16), INT_TO_BINARY(num >> 16), INT_TO_BINARY(num >> 8), INT_TO_BINARY(num));
    }
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Usage: %s <source .asm file>\n", argv[0]);
        return 1;
    }

    FILE *asmFile;
    asmFile = fopen(argv[1], "r");
    if (!asmFile)
    {
        printf("Can not open the .asm file\n");
        return 1;
    }

    FILE *txtFile;
    txtFile = fopen("machineCode.txt", "w");
    if (!txtFile)
    {
        printf("Can not open the .txt file\n");
        return 1;
    }

    if (FOR_LOGISIM)
        fprintf(txtFile, "v2.0 raw\n");

    char line[CHUNK_SIZE];
    while (fgets(line, 256, asmFile) != NULL)
    {
        int Bin = 0;

        // IGNORE COMMENTS
        char *comment_start = strstr(line, "--");
        if (comment_start)
            *comment_start = '\0';

        // TOKENIZE
        char **parts;
        int index = 0;
        parts[index++] = strtok(line, " \n\t");
        while (parts[index] != NULL)
            parts[index++] = strtok(NULL, " \n\t");


        if (strcmp(parts[1], "NUM") == 0)
        {
            int Code1 = atoi(parts[2]);
            Bin = Code1;
        }
        else
        {
            int Inst1 = getOpcode(parts[1]);

            if (parts[2] == NULL)
                parts[2] = "0";

            int Opnd1 = atoi(parts[2]);

            // Little tricky!
            Inst1 = Inst1 << 16;
            Bin = Opnd1 + Inst1; // To write, in a 32-bit form
        }

        output(Bin, txtFile);
    }

    return 0;
}