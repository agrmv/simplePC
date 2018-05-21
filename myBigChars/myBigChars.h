#pragma once
#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <inttypes.h>
#include <string.h>
#include <myTerm.h>

#define ENTER_ALT_MODE "\E(0"
#define EXIT_ALT_MODE "\E(B"
#define HORIZONTAL "q"
#define VERTICAL "x"
#define DL_ANGLE "m"
#define DR_ANGLE "j"
#define TL_ANGLE "l"
#define TR_ANGLE "k"
#define ACS_CKBOARD "a"

int bc_printA(const char* str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(int *big, int x, int y, eColors fgcolor, eColors bgcolor);
int bc_setbigcharpos(int* big, int x, int y, int value);
int bc_getbigcharpos(const int* big, int x, int y, int *value);
int bc_bigcharwrite(int fd, int* big, int count);
int bc_bigcharread(int fd, int* big, int need_count, int* count);