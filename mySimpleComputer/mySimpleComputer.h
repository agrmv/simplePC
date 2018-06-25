#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <iso646.h>
#include <stdbool.h>
#define SIZE 100

enum {
    FLAG_OUT_RANGE,
    FLAG_INVALID_COMMAND,
    FLAG_OVERFLOW,
    FLAG_DIV_ZERO,
    FLAG_IGNORE_CLOCK,
    FLAGS_END,
};

static int memory[SIZE];
static int _register;
extern int instructionCounter;
extern int accumulator;

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(const char *filename);
int sc_memoryLoad(const char *filename);
int sc_regInit();
int sc_regSet(int adress, int value);
int sc_regGet(int adress, int *value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);
int sc_isCommand(int value);