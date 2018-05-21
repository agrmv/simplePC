#include <myBigChars.h>
#include <mySimpleComputer.h>
#include  "interface.h"
#include "handler.h"
#include "IO.h"
static eColors tColor, bColor;

int big[][2] = {
        {0xC3C3C3FF, 0xFFC3C3C3}, //0
        {0xC0F0E0C0, 0xC0C0C0C0}, //1
        {0x3060C37E, 0xFF03060C}, //2
        {0x78C0C37E, 0x7EC3C0C0}, //3
        {0x666C7870, 0x606060FF}, //4
        {0x7F0303FF, 0x7EC1C0C0}, //5
        {0x7F03837E, 0x7EC3C3C3}, //6
        {0x3060C0FF, 0x03060C18}, //7
        {0x7EC3C37E, 0x7EC3C3C3}, //8
        {0xFEC3C37E, 0x7EC1C0C0}, //9
        {0x6666663C, 0x66667E66}, //A
        {0x7FC3C37F, 0x7FC3C3C3}, //B
        {0x0303C37E, 0x7EC30303}, //C
        {0xC3C3C37F, 0x7FC3C3C3}, //D
        {0x1F03037F, 0x7F030303}, //E
        {0x1F03037F, 0x03030303}, //F
        {0xFF3C3C00, 0x003C3CFF}  //+
};

void printBox(const char* title, int x, int y, int width, int height) {
    bc_box(x, y, height, width);
    mt_gotoXY(x, (y + width / 2 - strlen(title) / 2));
    printf(title);
}

void interfaceLoad(eColors textColor, eColors background) {
    mt_setfgcolor(textColor);
    mt_setbgcolor(background);
    tColor = textColor;
    bColor = background;
    printInterface();
}

void printInterface() {
    mt_clrscr();
    drawMemory(placeCellMemory.x, placeCellMemory.y);
    printAccum();
    printCounter();
    printFlags();
    printKeys();
    drawBigChar(placeCellMemory.x * 10 + placeCellMemory.y);
    printIO();
}

void printAccum() {
    printBox("Accumulator", 1, 63, 20, 3);
    mt_gotoXY(2, 71);
    printf("+%.4X", accumulator);
}

void printCounter() {
    printBox("instructionCounter", 4, 63, 20, 3);
    mt_gotoXY(5, 71);
    printf("+%.4X", instructionCounter);
}

void printOper(int value) {
    int command = 0, operand = 0;
    mt_gotoXY(8, 69);
    sc_commandDecode(value, &command, &operand);
    printf("%c%02X : %02X", command != 0 ? '+' : ' ', command, operand);
    printBox("Operation", 7, 63, 20, 3);
}

void drawMemory(int x_current, int y_current) {
    printBox("Memory", 1, 1, 62, 12);
    int value;
    char buf[10];
    for (int row = 0; row < 10; ++row) {
        mt_gotoXY(2 + row, 2);
        for (int column = 0; column < 10; ++column) {
            sc_memoryGet(row * 10 + column, &value);
            printMemoryCell(buf, value);
            if ((row == x_current) && (column == y_current)) {
                mt_setbgcolor(GREEN);
                mt_setfgcolor(RED);

            }
            if ((row == instructionCounter / 10) && (column == instructionCounter % 10)) {
                mt_setfgcolor(BLUE);

            }
            printf(buf);
            if ((row == instructionCounter / 10) && (column == instructionCounter % 10)) {
                mt_setfgcolor(DEFAULT);
            }
            if ((row == x_current) && (column == y_current)) {
                mt_setbgcolor(DEFAULT);
                mt_setfgcolor(DEFAULT);
            }
        }
        printf("\n");
    }
}

void printMemoryCell(char* buf, int value) {
    if (sc_isCommand(value)) {
        int cmd, operand;
        sc_commandDecode(value, &cmd, &operand);
        sprintf(buf, "+%02X%02X ", cmd, operand);
    }
    else
        sprintf(buf, " %04X ", value & 0x3FFF);

}

void printFlags() {
    printBox("Flags", 10, 63, 20, 3);
    char flags[13] = {0};
    int flagStatus = 0;
    if (!sc_regGet(FLAG_IGNORE_CLOCK, &flagStatus) && flagStatus) {
        strcat(flags, "T");
    } else {
        strcat(flags, "-");
    }
    if (!sc_regGet(FLAG_INVALID_COMMAND, &flagStatus) && flagStatus) {
        strcat(flags, " Е");
    }  else {
        strcat(flags, " -");
    }
    if (!sc_regGet(FLAG_OUT_RANGE, &flagStatus) && flagStatus) {
        strcat(flags, " М");
    }  else {
        strcat(flags, " -");
    }
    if (!sc_regGet(FLAG_OVERFLOW, &flagStatus) && flagStatus) {
        strcat(flags, " П");
    }  else {
        strcat(flags, " -");
    }
    if (!sc_regGet(FLAG_DIV_ZERO, &flagStatus) && flagStatus) {
        strcat(flags, " 0");
    }  else {
        strcat(flags, " -");
    }
    mt_gotoXY(11, 69);
    printf(flags);
}

void printKeys() {
    printBox("Keys", 13, 48, 35, 10);
    mt_gotoXY(14, 49);
    printf("l  - load");
    mt_gotoXY(15, 49);
    printf("s  - save");
    mt_gotoXY(16, 49);
    printf("r  - run");
    mt_gotoXY(17, 49);
    printf("t  - step");
    mt_gotoXY(18, 49);
    printf("i  - reset");
    mt_gotoXY(19, 49);
    printf("F5 - accumulator");
    mt_gotoXY(20, 49);
    printf("F6 - instructionCounter");
}

void drawBigChar(int address) {
    int value;
    sc_memoryGet(address, &value);
    char buf[6];
    printMemoryCell(buf, value);
    printOper(value);
    for (int i = 0; i < strlen(buf); ++i) {
        switch (buf[i]) {
            case '+' :
                bc_printbigchar(big[16], 14, 2, tColor, bColor);
                break;
            case '0':
                bc_printbigchar(big[0], 14, (2 + i * 9), tColor, bColor);
                break;
            case '1':
                bc_printbigchar(big[1], 14, (2 + i * 9), tColor, bColor);
                break;
            case '2':
                bc_printbigchar(big[2], 14, (2 + i * 9), tColor, bColor);
                break;
            case '3':
                bc_printbigchar(big[3], 14, (2 + i * 9), tColor, bColor);
                break;
            case '4':
                bc_printbigchar(big[4], 14, (2 + i * 9), tColor, bColor);
                break;
            case '5':
                bc_printbigchar(big[5], 14, (2 + i * 9), tColor, bColor);
                break;
            case '6':
                bc_printbigchar(big[6], 14, (2 + i * 9), tColor, bColor);
                break;
            case '7':
                bc_printbigchar(big[7], 14, (2 + i * 9), tColor, bColor);
                break;
            case '8':
                bc_printbigchar(big[8], 14, (2 + i * 9), tColor, bColor);
                break;
            case '9':
                bc_printbigchar(big[9], 14, (2 + i * 9), tColor, bColor);
                break;
            case 'A':
                bc_printbigchar(big[10], 14, (2 + i * 9), tColor, bColor);
                break;
            case 'B':
                bc_printbigchar(big[11], 14, (2 + i * 9), tColor, bColor);
                break;
            case 'C':
                bc_printbigchar(big[12], 14, (2 + i * 9), tColor, bColor);
                break;
            case 'D':
                bc_printbigchar(big[13], 14, (2 + i * 9), tColor, bColor);
                break;
            case 'E':
                bc_printbigchar(big[14], 14, (2 + i * 9), tColor, bColor);
                break;
            case 'F':
                bc_printbigchar(big[15], 14, (2 + i * 9), tColor, bColor);
                break;
            default:
                break;
        }
    }
    bc_box(13, 1, 10, 47);
    mt_gotoXY(24, 1);
    fflush(stdout);
}

void printIO() {
    mt_gotoXY(23, 1);
    printf(" I/O\n ");
    printf(IO);
    fflush(stdout);
}