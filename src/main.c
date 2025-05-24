// src/main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "keyboard.h"
#include "screen.h"
#include "timer.h"

#define MENU_TXT       "src/arquivos/menu.txt"
#define GAMEOVER_TXT   "src/arquivos/gameover.txt"
#define SCORE_TXT      "src/arquivos/score.txt"
#define MAX_NAME_LEN   50
#define MAX_ENTRIES    100
#define TOP_N          3

typedef struct Node {
    int x, y;
    struct Node *next;
} Node;

typedef struct {
    int score;
    char name[MAX_NAME_LEN];
} ScoreEntry;

static int compare_scores(const void *a, const void *b) {
    const ScoreEntry *s1 = a, *s2 = b;
    return s2->score - s1->score;
}

void exibir_arquivo(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) return;
    char linha[200];
    while (fgets(linha, sizeof linha, f))
        printf("%s", linha);
    fclose(f);
    printf("\n");
}

void aguardar_tecla() {
    while (!keyhit()) {}
    readch();
}

void carregar_scores(ScoreEntry entries[], int *count) {
    *count = 0;
    FILE *f = fopen(SCORE_TXT, "r");
    if (!f) return;
    while (*count < MAX_ENTRIES &&
           fscanf(f, "%d %49[^\n]\n",
                  &entries[*count].score,
                  entries[*count].name) == 2) {
        (*count)++;
    }
    fclose(f);
}

void salvar_top_scores(ScoreEntry entries[], int count) {
    FILE *f = fopen(SCORE_TXT, "w");
    if (!f) return;
    int n = count < TOP_N ? count : TOP_N;
    for (int i = 0; i < n; i++)
        fprintf(f, "%d %s\n", entries[i].score, entries[i].name);
    fclose(f);
}

void exibir_scores() {
    ScoreEntry entries[MAX_ENTRIES];
    int count;
    carregar_scores(entries, &count);
    if (count == 0) {
        printf("Nenhuma pontuação salva ainda.\n\n");
        return;
    }
    qsort(entries, count, sizeof *entries, compare_scores);
    printf("=== TOP %d SCORES ===\n", TOP_N);
    for (int i = 0; i < count && i < TOP_N; i++)
        printf("%d. %s — %d\n", i+1, entries[i].name, entries[i].score);
    printf("\n");
}

void addObstacle(Node **head, int x, int y) {
    int cnt = 0;
    for (Node *p = *head; p; p = p->next) cnt++;
    if (cnt >= MAX_ENTRIES) return;
    Node *novo = malloc(sizeof *novo);
    novo->x = x; novo->y = y; novo->next = NULL;
    if (!*head) *head = novo;
    else {
        Node *p = *head;
        while (p->next) p = p->next;
        p->next = novo;
    }
}

void updateObstacles(Node **head, int *score) {
    Node *p = *head, *prev = NULL;
    while (p) {
        p->x--;
        if (p->x <= 0) {
            (*score)++;
            Node *t = p;
            if (prev) prev->next = p->next;
            else       *head    = p->next;
            p = p->next;
            free(t);
        } else {
            prev = p;
            p = p->next;
        }
    }
}

void freeObstacles(Node *head) {
    while (head) {
        Node *t = head->next;
        free(head);
        head = t;
    }
}

int main() {
    const int dogX    = 5;
    const int groundY = MAXY - 1;
    int jump = 0, jumpTimer = 0;
    int score = 0, ch = 0;

    // Exemplo de matriz dinâmica
    char **screen_buf = malloc(MAXY * sizeof(char*));
    for (int y = 0; y < MAXY; y++)
        screen_buf[y] = malloc(MAXX * sizeof(char));

    Node *obstacles = NULL;

    srand((unsigned)time(NULL));
    screenInit(0);
    keyboardInit();
    timerInit(100);

    // Tela de menu
    screenClear();
    exibir_arquivo(MENU_TXT);
    exibir_scores();
    aguardar_tecla();

    // Loop principal
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
            updateObstacles(&obstacles, &score);
            if (rand() % 20 == 0)
                addObstacle(&obstacles, MAXX - 2, groundY);
        }

        screenClear();
        // substituição do operador ternário
        int offset = 0;
        if (jump) {
            offset = 4;
        }
        int dogY = groundY - offset;

        screenGotoxy(dogX, dogY);
        printf("🐶");
        for (Node *p = obstacles; p; p = p->next) {
            screenGotoxy(p->x, p->y);
            printf("🧱");
            if (p->x == dogX && dogY == groundY)
                ch = 27;
        }
        screenGotoxy(0, 0);
        printf("Score: %d", score);
        screenUpdate();
    }

    // Game Over
    screenClear();
    exibir_arquivo(GAMEOVER_TXT);
    screenGotoxy(MAXX/2 - 8, MAXY/2 + 2);
    printf("Pontuação final: %d\n", score);

    // Top 3
    ScoreEntry entries[MAX_ENTRIES];
    int count;
    carregar_scores(entries, &count);

    int qualifies = (count < TOP_N) ||
                    (score > entries[TOP_N-1].score);
    if (qualifies) {
        char name[MAX_NAME_LEN] = "Anon";
        keyboardDestroy();
        screenShowCursor();
        screenGotoxy(MAXX/2 - 8, MAXY/2 + 4);
        printf("Novo TOP %d! Digite seu nome: ", TOP_N);
        fflush(stdout);
        if (fgets(name, sizeof name, stdin))
            name[strcspn(name, "\n")] = '\0';
        screenHideCursor();
        keyboardInit();

        if (count < MAX_ENTRIES) count++;
        entries[count-1].score = score;
        strncpy(entries[count-1].name, name, MAX_NAME_LEN-1);
        entries[count-1].name[MAX_NAME_LEN-1] = '\0';

        qsort(entries, count, sizeof *entries, compare_scores);
        salvar_top_scores(entries, count);
    }

    screenUpdate();
    aguardar_tecla();

    // Cleanup
    freeObstacles(obstacles);
    for (int y = 0; y < MAXY; y++) free(screen_buf[y]);
    free(screen_buf);

    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    return 0;
}
