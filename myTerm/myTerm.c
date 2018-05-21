#include "myTerm.h"

int mt_clrscr() {
    printf(CLEAR_SCREEN);
    return 0;
}

int mt_gotoXY(int x, int y) {
    if (x < 0 || y < 0) {
        return -1;
    }
    int max_x, max_y;
    if (mt_getscreensize(&max_x, &max_y) || max_x < x || max_y < y) {
        return -1;
    }
    printf(CURSOR_SET_FORMAT, x, y);
    return 0;
}

int mt_getscreensize(int *rows, int *cols) {
    if (rows && cols) {
        struct winsize ws;
        if (!ioctl(1, TIOCGWINSZ, &ws)) {
            *rows = ws.ws_row;
            *cols = ws.ws_col;
            return 0;
        }
    }
    perror("ERROR SCREEN SIZE");
    return -1;
}

int mt_setfgcolor(eColors color) {
    if (color < BLACK || color > DEFAULT) {
        perror("COLOR != ENUM");
        return -1;
    }
    printf(FOREGR_SET_FORMAT, color);
    return 0;
}

int mt_setbgcolor(eColors color) {
    if (color < BLACK || color > DEFAULT) {
        perror("COLOR != ENUM");
        return -1;
    }
    printf(BACKGR_SET_FORMAT, color);
    return 0;
}

int mt_reset() {
    printf(GR_RESET);
    mt_clrscr();
    return 0;
}