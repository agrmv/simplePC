#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <iso646.h>
#include <sys/ioctl.h>
#include <inttypes.h>
#define CLEAR_SCREEN "\E[H\E[J"
#define BACKGR_SET_FORMAT "\E[4%dm"
#define FOREGR_SET_FORMAT "\E[3%dm"
#define CURSOR_SET_FORMAT "\E[%d;%dH"
#define GR_RESET "\E[0m"
typedef enum {
    BLACK = 0,  //always first
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    WHITE,
    DEFAULT  = 9   //always last
} eColors;

int mt_clrscr();
int mt_gotoXY(int, int);
int mt_getscreensize(int*, int*);
int mt_setfgcolor(eColors colors);
int mt_setbgcolor(eColors colors);
int mt_reset();