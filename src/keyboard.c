#include "keyboard.h"
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdio.h>

static struct termios oldt, newt;

void keyboardInit() {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void keyboardDestroy() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int keyhit() {
    struct timeval tv = {0, 0};
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);
    return select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv) > 0;
}

int readch() {
    return getchar();
}
