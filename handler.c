#include <myBigChars.h>
#include "handler.h"
#include "IO.h"
#include "interface.h"
#include "../cpu.h"

void signalhangle(int signal) {
    switch (signal) {
        case SIGALRM: {
            int val;
            if (!sc_regGet(FLAG_IGNORE_CLOCK, &val) && !val) {
                CU();
                printInterface();
            }
        }
            break;
        case SIGUSR1: {
            sc_regInit();
            instructionCounter = 0;
            accumulator = 0;
            sc_regSet(FLAG_IGNORE_CLOCK, 1);
        }
            break;
        default:break;
    }
}

void create_timer(double interval) {
    struct itimerval nval;
    nval.it_value.tv_sec = nval.it_interval.tv_sec = (size_t)interval;
    nval.it_value.tv_usec = nval.it_interval.tv_usec = (size_t)((interval - (size_t)interval) * 1000000);
    setitimer (ITIMER_REAL, &nval, NULL);
}

void handlerKey(eKeys key) {
    switch (key) {
        case KEY_RUN:
            handlerRun();
            break;;
        case KEY_UP:
            --placeCellMemory.x;
            if (placeCellMemory.x == -1) {
                placeCellMemory.x = 9;
            }
            drawMemory(placeCellMemory.x, placeCellMemory.y);
            drawBigChar(placeCellMemory.x * 10 + placeCellMemory.y);
            break;
        case KEY_DONW:
            ++placeCellMemory.x;
            if (placeCellMemory.x == 10) {
                placeCellMemory.x = 0;
            }
            drawMemory(placeCellMemory.x, placeCellMemory.y);
            drawBigChar(placeCellMemory.x * 10 + placeCellMemory.y);
            break;
        case KEY_RIGHT:
            ++placeCellMemory.y;
            if (placeCellMemory.y == 10) {
                placeCellMemory.y = 0;
            }
            drawMemory(placeCellMemory.x, placeCellMemory.y);
            drawBigChar(placeCellMemory.x * 10 + placeCellMemory.y);
            break;
        case KEY_LEFT:
            --placeCellMemory.y;
            if (placeCellMemory.y == -1) {
                placeCellMemory.y = 9;
            }
            drawMemory(placeCellMemory.x, placeCellMemory.y);
            drawBigChar(placeCellMemory.x * 10 + placeCellMemory.y);
            break;
        case KEY_F5:
            handlerLoadAccum();
            break;
        case KEY_F6:
            handlerLoadInstructionCounter();
            break;
        case KEY_QUIT:
            handlerQuit();
            break;
        case KEY_LOAD:
            handlerLoad();
            break;
        case KEY_SAVE:
            handlerSave();
            break;
        case KEY_STEP:
            handlerStep();
            break;
        case KEY_ENTER:
            handlerLoadCellMemory(placeCellMemory.x, placeCellMemory.y);
            break;
        case KEY_RESET:
            handlerReset();
            break;
    }
}

void handlerLoad() {
    drawLoadSaveMemory();
    char *buf = readConsole();
    if (buf) {
        if (sc_memoryLoad(buf) != 0) {
            addMessage("Error load memory file!");
        }
    }
    printInterface();
    free(buf);
}

void handlerSave() {
    drawLoadSaveMemory();
    char *buf = readConsole();
    if (buf) {
        if (sc_memorySave(buf) != 0) {
            addMessage("Error save memory file!");
        }
    }
    printInterface();
    free(buf);
}

void handlerLoadCellMemory(int place_x, int place_y) {
    drawLoadCell();
    char *buf = readConsole();
    if (buf) {
        int val;
        if (decodeVal(buf, &val) != -1) {
            sc_memorySet(place_x * 10 + place_y, val);
        } else {
            addMessage("Could not set cell value");
        }
    }
    printInterface();
    free(buf);
}

void handlerRun() {
    sc_regSet(FLAG_IGNORE_CLOCK, 0);
    create_timer(0.1);
    printInterface();
}

void handlerQuit() {
    mt_clrscr();
    mt_reset();
}

void handlerStep() {
    sc_regSet(FLAG_IGNORE_CLOCK, 0);
    alarm(1);
    printInterface();
}

void handlerReset() {
    create_timer(0);
    raise(SIGUSR1);
    sc_memoryInit();
    *io_msg = '\0';
    printInterface();
}

void initHandler() {
    placeCellMemory.x = 0;
    placeCellMemory.y = 0;
    signal(SIGUSR1, signalhangle);
    signal(SIGALRM, signalhangle);
    eKeys key;
    do {
        rk_readkey(&key);
        handlerKey(key);
    } while (key != KEY_QUIT);
    int max_x, max_y;
    mt_getscreensize(&max_x, &max_y);
    mt_gotoXY(1, 1);

}

int decodeVal(char *buf, int *val) {
    if (buf[0] == '+') {
        if (strlen((const char *) buf) > 5) {
            return -1;
        }
        *val = atoi(&buf[1]);
        if (*val < 0x7fff) {
            return  0;
        }
    } else {
        return -1;
    }
}

void handlerLoadAccum() {
    drawLoadCell();
    char *buf = readConsole();
    if (buf) {
        if (decodeVal(buf, &accumulator) != -1) {
        } else {
            addMessage("Could not set accumulator value");
        }
    }
    printInterface();
    free(buf);
}

void handlerLoadInstructionCounter() {
    drawLoadCell();
    char *buf = readConsole();
    if (buf) {
        if (decodeVal(buf, &instructionCounter) != -1) {
        } else {
            addMessage("Could not set instructionCounter value");
        }
    }
    printInterface();
    free(buf);
}