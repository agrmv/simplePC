#include <myBigChars.h>
#include "IO.h"
#include "handler.h"

int addMessage(char *message) {
    //strcpy(IO, message);
    strcat(IO, message);
    strcat(IO, "\n");
    return 0;
}

char *readConsole() {
    char *buffer = malloc(sizeof(buffer));
    ssize_t  num = read(STDIN_FILENO, buffer, 100);
    buffer[num - 1] = '\0';
    return buffer;
}


void writeConsoleValue(int addr, int value) {
    char print[16];
    sprintf(print, "%d>\t%0X", addr, value);
    addMessage(print);
}

void readConsoleValue(int addr, int *value) {
    drawLoadCell();
    rk_mytermregime(0, 0, 1, 1, 1);
    scanf("%X", value);
    if (*value < 0x7fff) {
        char print[16];
        sprintf(print, "%d<\t%0X", addr, *value);
        addMessage(print);
    } else {
        addMessage("Wrong format of value");
    }
}

void drawLoadCell() {
    mt_setbgcolor(CYAN);
    mt_setfgcolor(RED);
    bc_box(5, 20, 6, 23);
    for (int i = 6; i < 10; ++i) {
        for (int j = 21; j < 42; ++j) {
            mt_gotoXY(i, j);
            printf(" ");
        }
    }

    mt_gotoXY(6, 22);
    printf("Enter Value");
    bc_box(7, 21, 3, 21);
    fflush(stdout);
    mt_setfgcolor(DEFAULT);
    mt_setbgcolor(DEFAULT);
}

void drawLoadSaveMemory() {
    mt_setbgcolor(CYAN);
    mt_setfgcolor(RED);
    bc_box(5, 20, 6, 23);
    for (int i = 6; i < 10; ++i) {
        for (int j = 21; j < 42; ++j) {
            mt_gotoXY(i, j);
            printf(" ");
        }
    }
    mt_gotoXY(6, 22);
    printf("Enter File Name");
    bc_box(7, 21, 3, 21);
    fflush(stdout);
    mt_setfgcolor(DEFAULT);
    mt_setbgcolor(DEFAULT);
}