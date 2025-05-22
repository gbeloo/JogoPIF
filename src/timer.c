#include "timer.h"
#include <time.h>
#include <stdio.h>

static struct timespec last;
static int interval_ms;

void timerInit(int valueMilliSec) {
    interval_ms = valueMilliSec;
    clock_gettime(CLOCK_MONOTONIC, &last);
}

void timerDestroy() {
    // nada a fazer
}

void timerUpdateTimer(int valueMilliSec) {
    interval_ms = valueMilliSec;
}

int timerTimeOver() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    long diff = (now.tv_sec - last.tv_sec) * 1000
              + (now.tv_nsec - last.tv_nsec) / 1000000;
    if (diff >= interval_ms) {
        last = now;
        return 1;
    }
    return 0;
}

void timerPrint() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    long diff = (now.tv_sec - last.tv_sec) * 1000
              + (now.tv_nsec - last.tv_nsec) / 1000000;
    printf("Timer: %ld ms\n", diff);
}
