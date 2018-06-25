#pragma once
#include <stdint.h>
char io_msg[1024];

void addMessage(char *);
char *readConsole();
void writeConsoleValue(int addr, int value);
void readConsoleValue(int addr, int *value);
void drawLoadCell();
void drawLoadSaveMemory();