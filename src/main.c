#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>      // para sleep()

#include "keyboard.h"
#include "screen.h"
#include "timer.h"

#define MAX_OBSTACULOS 5

typedef struct {
    int x, y;
    int active;
} Obstaculo;

int main() {
    const int dogX    = 5;
    const int groundY = MAXY - 1;
    int       jump    = 0, jumpTimer = 0;
    Obstaculo obstacles[MAX_OBSTACULOS] = {0};
    int       score   = 0;
    int       ch      = 0;

    srand((unsigned)time(NULL));
    screenInit(0);      // sem bordas
    keyboardInit();
    timerInit(100);     // 100 ms por frame

    while (ch != 27) {
        if (keyhit()) {
            ch = readch();
            if ((ch == ' ' || ch == 'w') && !jump) {
                jump = 1;
                jumpTimer = 5;
            }
        }

        if (timerTimeOver()) {
            if (jump && --jumpTimer <= 0) jump = 0;
            for (int i = 0; i < MAX_OBSTACULOS; i++) {
                if (obstacles[i].active) {
                    obstacles[i].x--;
                    if (obstacles[i].x <= 0) {
                        obstacles[i].active = 0;
                        score++;
                    }
                }
            }
            if (rand() % 20 == 0) {
                for (int i = 0; i < MAX_OBSTACULOS; i++) {
                    if (!obstacles[i].active) {
                        obstacles[i].active = 1;
                        obstacles[i].x      = MAXX - 2;
                        obstacles[i].y      = groundY;
                        break;
                    }
                }
            }
        }

        screenClear();
        int dogY = groundY - (jump ? 4 : 0);
        screenGotoxy(dogX, dogY);
        printf("D");

        for (int i = 0; i < MAX_OBSTACULOS; i++) {
            if (obstacles[i].active) {
                screenGotoxy(obstacles[i].x, obstacles[i].y);
                printf("#");
                if (obstacles[i].x == dogX && dogY == groundY) {
                    ch = 27;
                }
            }
        }

        screenGotoxy(0, 0);
        printf("Score: %d", score);
        screenUpdate();
    }

    screenClear();
    screenGotoxy(MAXX/2 - 6, MAXY/2);
    printf(" GAME OVER ");
    screenGotoxy(MAXX/2 - 8, MAXY/2 + 1);
    printf("Final Score: %d", score);
    screenUpdate();
    sleep(2);

    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    return 0;
}
