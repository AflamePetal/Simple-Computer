# Simple-Computer

## Instruction Set

The system follows the instruction set below:

```
Inst    Opcode
================
JMP     0001
JRP     0010
LDN     0011
STO     0100
SKN     0101
SUB     0110
ADD     0111
MUL     1000
DIV     1001
NEG     1010
AND     1011
OR      1100
NOT     1101
HLT     1110
```

## Architecture

This machine is an **accumulator-based, open-looped von Neumann architecture** with minimal pipelining.
Unlike traditional pipeline architectures, it does not have clearly defined pipeline stages. Instead, it operates on a **dual-tick clock cycle**, where all components function based on these two ticks.

## Running the Machine

To test the system, use **Logisim Evolution**:
1. Open the `.circ` file in Logisim Evolution.
2. Load the machine code (in hexadecimal format) into RAM.
3. Run the machine.

---

# Assembler

A simple assembler is provided to convert assembly code into machine code.

### Usage

Run the assembler from the command line:

```sh
assemble myFile.asm
```

The assembler will generate a machine code file in either **binary** or **hexadecimal** format.

- If the `FOR_LOGISIM` flag in the source file is set to `true`, the output will be in **hexadecimal** format.
- Otherwise, the output will be in **binary** format.

Simple assembly test files are included for testing the machine.
