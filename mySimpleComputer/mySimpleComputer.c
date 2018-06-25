#include "mySimpleComputer.h"

int instructionCounter = 0;
int accumulator = 0;

int sc_memoryInit() {
    for (int i = 0; i < SIZE; ++i)
        memory[i] = 0;
    return 0;
}

int sc_memorySet(int address, int value) {
    if (address < 0 || address > SIZE - 1) {
        sc_regSet(FLAG_OUT_RANGE, 1);
        return 1;
    }
    memory[address] = value;
    return 0;
}

int sc_memoryGet(int address, int *value) {
    if (address < 0 || address > SIZE - 1) {
        sc_regSet(FLAG_OUT_RANGE, 1);
        return 1;
    }
    *value = memory[address] & 0x7FFF;
    return 0;
}

int sc_memorySave(const char *filename) {
    FILE *fout = fopen(filename, "wb");
    if (fout) {
        fwrite(memory, sizeof(int), SIZE, fout);
        fclose(fout);
        return 0;
    }
    return 1;
}

int sc_memoryLoad(const char *filename) {
    FILE *fin = fopen(filename, "rb");
    if (fin) {
        fread(memory, sizeof(int), SIZE, fin);
        fclose(fin);
        return 0;
    }
    return 1;
}

int sc_regInit() {
    return (_register = 0);
}

int sc_regSet(int reg, int value) {
    if (reg < 0 || reg >= FLAGS_END)
        return 1;
    if (value == 1)
        _register |= 1 << reg;
    else if (value == 0)
        _register &= ~(1 << reg);
    else
        return 1;
    return 0;
}

int sc_regGet(int reg, int *value) {
    if (reg < 0 || reg >= FLAGS_END)
        return 1;
    *value = (_register >> reg) & 0x1;
    return 0;
}

int sc_commandEncode(int command, int operand, int *value) {
    if (operand < 0 || operand >= SIZE)            //operand is incorrect
        return 1;
    if (command < 0x10 || command > 0x11 && command < 0x20 ||     //command is incorrect
        command > 0x21 && command < 0x30 || command > 0x33 && command < 0x40 ||
        command > 0x43 && command < 0x51 || command > 0x76)
        return 1;
    *value = 0x3FFF & (command << 7 | operand);
    return 0;
}

int sc_isCommand(int value) {
    return !(value & 0x4000);
}

int sc_commandDecode(int value, int *command, int *operand) {
    if (value & ~0x3FFF) {
        sc_regSet(FLAG_INVALID_COMMAND, 1);
        return 1;
    }
    *operand = value & 0x7F;
    *command = (value >> 7) & 0x7F;
    return 0;
}
