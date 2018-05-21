#include "myReadKey.h"

static struct termios option;

int rk_mytermregime(int regime, cc_t vtime, cc_t vmin, int echo, int sigint) {

    struct termios option;
    if (tcgetattr(STDIN_FILENO, &option) != 0) {
        return -1;
    }
    if (regime) {
        option.c_lflag |= ICANON;
    } else {
        option.c_lflag &= ~ICANON;
        if (echo) {
            option.c_lflag |= ECHO;
        } else {
            option.c_lflag &= ~ECHO;
        }
        if (sigint) {
            option.c_lflag |= ISIG;
        } else {
            option.c_lflag &= ~ISIG;
        }
        option.c_cc[VMIN] = vmin;
        option.c_cc[VTIME] = vtime;
    }
    if (tcsetattr(STDIN_FILENO, TCSANOW, &option) != 0) {
        return -1;
    }
    return 0;

}

int rk_mytermsave () {
    return tcgetattr(STDIN_FILENO, &option);
}

int rk_mytermrestore () {
    return tcsetattr(STDIN_FILENO, TCSANOW, &option);
}

int rk_readkey(eKeys *press_key) {
    char key[8];
    if (rk_mytermsave() || rk_mytermregime(0, 0, 1, 0, 0))
        return -1;
    ssize_t reads = read(STDIN_FILENO, key, 7);
    if (reads <= 0)
        return -1;
    key[reads] = 0;
    *press_key = KEY_UNKNOWN;
    if (key[0] == '\033') { // \E
        if (!strcmp(key, F5))
            *press_key = KEY_F5;
        else if (!strcmp(key, F6))
            *press_key = KEY_F6;
        else if (!strcmp(key, UP))
            *press_key = KEY_UP;
        else if (!strcmp(key, DOWN))
            *press_key = KEY_DONW;
        else if (!strcmp(key, RIGHT))
            *press_key = KEY_RIGHT;
        else if (!strcmp(key, LEFT))
            *press_key = KEY_LEFT;

    } else {
        if (key[0] >= 'A' && key[0] <= 'Z')
            key[0] -= 'A' - 'a';
        switch (key[0]) {
            case 'l': *press_key = KEY_LOAD; break;
            case 's': *press_key = KEY_SAVE; break;
            case 'r': *press_key = KEY_RUN; break;
            case 't': *press_key = KEY_STEP; break;
            case 'i': *press_key = KEY_RESET; break;
            case 'q': *press_key = KEY_QUIT; break;
            case '\n': *press_key =KEY_ENTER; break;
            default:break;
        }
    }
    return rk_mytermrestore();
}