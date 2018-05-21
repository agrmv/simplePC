#pragma once
#include "IO.h"
#include "myTerm.h"

typedef struct {
    int x;
    int y;
} callMemory;
callMemory placeCellMemory;


void interfaceLoad(eColors textColor, eColors background);
void printBox(const char* title, int x, int y, int width, int height);
void printInterface();
void printAccum();
void printCounter();
void printOper(int value);
void printFlags();
void printIO();
void printKeys();
void printMemoryCell(char* buf, int value);
void drawMemory(int x_current, int y_current);
void drawBigChar(int address);