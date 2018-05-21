#pragma once
#include <stdint.h>
char IO[1024];

int addMessage(char *);
char *readConsole();
void writeConsoleValue(int addr, int value);
void readConsoleValue(int addr, int *value);
void drawLoadCell();
void drawLoadSaveMemory();