#pragma once
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <myReadKey.h>
#include <myTerm.h>
#include <signal.h>
#include <mySimpleComputer.h>
#include <sys/time.h>
#include "interface.h"

void initHandler();
void handlerRun();
void handlerQuit();
void handlerStep();
void handlerReset();
void handlerLoad();
void handlerSave();
void handlerLoadAccum();
void handlerKey(eKeys key);
int decodeVal(char *buf, int *val);
void handlerLoadCellMemory(int place_x, int place_y);
void handlerLoadInstructionCounter();