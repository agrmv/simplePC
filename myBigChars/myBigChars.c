#include "myBigChars.h"

int bc_printA (const char* str) {
    if (!str) {
        return -1;
    }
    printf(ENTER_ALT_MODE"%s"EXIT_ALT_MODE, str);
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2) {
    if (x1 <= 0 || y1 <= 0 || x2 < 1 || y2 < 1)
        return -1;
    --y2, --x2;
    int mx, my;
    if (mt_getscreensize(&mx, &my) || mx < x1 + x2 || my < y1 + y2)
        return -1;
    int  x = x1, y = 0;

    char hline[y2];
    for (; y < y2 - 1; ++y)
        hline[y] = HORIZONTAL[0];
    hline[y] = 0;

    mt_gotoXY(x1, y1);
    bc_printA(TL_ANGLE);//corner ┌
    bc_printA(hline);       //upper hline
    bc_printA(TR_ANGLE);//corner ┐
    mt_gotoXY(x1 + x2, y1);
    bc_printA(DL_ANGLE);//corner └
    bc_printA(hline);       //lower hline
    bc_printA(DR_ANGLE);//corner ┘

    for (y = y1 + y2, ++x; x < x1 + x2; ++x) {  //vertical lines
        mt_gotoXY(x, y);
        bc_printA(VERTICAL);
        mt_gotoXY(x, y1);
        bc_printA(VERTICAL);
    }
}

int bc_printbigchar (int *big, int x, int y, eColors fgcolor, eColors bgcolor) {
    mt_setbgcolor(bgcolor);
    mt_setfgcolor(fgcolor);
    int value;
    int size_x = 8;
    int size_y = 8;
    for (int i = 0; i < size_x; ++i) {
        mt_gotoXY(x + i, y);
        for (int j = 0; j < size_y; ++j) {
            bc_getbigcharpos(big, i, j, &value);
            bc_printA(value ? ACS_CKBOARD : " ");
        }
    }
}

int bc_setbigcharpos(int* big, int x, int y, int value) {
    if (!big) {
        return -1;
    }
    big += (y >> 2) & 0x1;
    if (value & 0x1) {
        *big |= 1 << ((y & 0x3) * 8 + x);
    } else {
        *big &= ~(1 << ((y & 0x3) * 8 + x));
    }
    return 0;
}

int bc_getbigcharpos(const int* big, int x, int y, int *value) {
    if (!big || !value) {
        return -1;
    }
    *value = (big[(x >> 2) & 0x1] >> ((x & 0x3) * 8 + y)) & 0x1;
    return 0;
}

int bc_bigcharwrite(int fd, int* big, int count) {

    if (write(fd, big, count * (sizeof(int64_t)))==-1) {
        return -1;
    }
    return 0;
}

int bc_bigcharread(int fd, int* big, int need_count, int* count) {
    *count = read(fd, big, need_count * sizeof(int64_t)) / (sizeof(int64_t));
    if (*count == -1) {
        return -1;
    }

    *count /= (sizeof(int64_t));
    return 0;
}