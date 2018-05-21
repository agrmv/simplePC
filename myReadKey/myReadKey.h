#pragma once
#include <termios.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define UP    "\E[A"
#define DOWN  "\E[B"
#define RIGHT "\E[C"
#define LEFT  "\E[D"
#define F5    "\E[15~"
#define F6    "\E[17~"


typedef enum {
    KEY_UNKNOWN,
    KEY_UP = 1,
    KEY_DONW,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_F5,
    KEY_F6,
    KEY_QUIT,
    KEY_LOAD,
    KEY_SAVE,
    KEY_RUN,
    KEY_STEP,
    KEY_ENTER,
    KEY_RESET
} eKeys;

int rk_mytermregime(int regime, cc_t vtime, cc_t vmin, int echo, int sigint);
int rk_mytermsave();
int rk_mytermrestore();
int rk_readkey(eKeys *key);