#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InstCode.h"


#define FILE_NAME "D:/Personal Data/Programming Projects/C/SSEM Computer/asmFiles/Add.asm" //Change it to the LOCATION\NAME of your file that you want to assemble


#define CHUNK_SIZE 256

#define FOR_LOGISIM 1 // Set this to '1' if you want the output to use in logisim.

// This snippet is for printing an integer in its binary form
#define _8_BIT_PATTERN "%c%c%c%c%c%c%c%c"
#define INT_TO_BINARY(byte)          \
        ((byte) & 0x80 ? '1' : '0'), \
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

char **strSplit(char *asmCode)
{
    char *pos;
    pos = strstr(asmCode, "--");
    if (pos != NULL)
        strncpy(pos, "\0", 1);

    char *sPtr;
    char **parts = malloc(3 * sizeof(char *));
    int idx = 0;

    sPtr = strtok(asmCode, " \r\n\t");
    parts[idx++] = sPtr;
    while (sPtr != NULL)
    {
        sPtr = strtok(NULL, " \r\n\t");
        parts[idx++] = sPtr;
    }

    return parts;
}

int main()
{

    FILE *asmFile;
    asmFile = fopen(""FILE_NAME"", "rb");
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

    unsigned char buffer[CHUNK_SIZE];
    char *parts; // It will contain the parts of the code and not the comments
    size_t bytesRead;

    char ch = 0;
    char line[CHUNK_SIZE];
    int idx = 0;
    while (ch != EOF)
    {
        int Bin = 0;

        ch = fgetc(asmFile);
        line[idx++] = ch;
        if (ch == '\n' || ch == EOF)
        {
            line[idx] = '\0';
            char **parts = strSplit(line);
            char *str = parts[1];
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

                // Preparing the numbers for writing in binary form. Little tricky!
                Inst1 = Inst1 << 16;  // 4 bits for instruction code
                Bin = Opnd1 + Inst1; // For writing in 32 bits form we need to add these
            }

            output(Bin, txtFile);

            idx = 0;
            strcpy(line, " ");
        }
    }

    return 0;
}