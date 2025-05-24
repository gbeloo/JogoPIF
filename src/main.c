#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "keyboard.h"
#include "screen.h"
#include "timer.h"

#define MAX_OBSTACULOS 5
#define MENU_TXT "libary/menu.txt"
#define GAMEOVER_TXT "libary/gameover.txt"

typedef struct {
    int x, y;
    int active;
} Obstaculo;

void exibir_arquivo(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) return;
    char linha[200];
    while (fgets(linha, sizeof(linha), f)) {
        printf("%s", linha);
    }
    fclose(f);
    printf("\n");
}

void aguardar_tecla() {
    while (!keyhit()) {}
    readch();
}

int main() {
    const int dogX    = 5;
    const int groundY = MAXY - 1;
    int jump = 0, jumpTimer = 0;
    Obstaculo obstacles[MAX_OBSTACULOS] = {0};
    int score = 0;
    int ch = 0;

    srand((unsigned)time(NULL));
    screenInit(0);       // sem bordas
    keyboardInit();
    timerInit(100);      // 100 ms por frame

    // Tela de menu
    screenClear();
    exibir_arquivo(MENU_TXT);
    aguardar_tecla();

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
                        obstacles[i].x = MAXX - 2;
                        obstacles[i].y = groundY;
                        break;
                    }
                }
            }
        }

        screenClear();
        int dogY = groundY - (jump ? 4 : 0);
        screenGotoxy(dogX, dogY);
        printf("🐶");

        for (int i = 0; i < MAX_OBSTACULOS; i++) {
            if (obstacles[i].active) {
                screenGotoxy(obstacles[i].x, obstacles[i].y);
                printf("🌵");
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
    exibir_arquivo(GAMEOVER_TXT);
    screenGotoxy(MAXX / 2 - 8, MAXY / 2 + 2);
    printf("Pontuação final: %d\n", score);
    screenUpdate();
    aguardar_tecla();

    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    return 0;
}


