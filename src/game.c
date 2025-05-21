#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

#include <keyboard.h>
#include <screen.h>
#include <timer.h>

Game* init_game() {
    Game *game = malloc(sizeof(Game));
    game->player.x = 5;
    game->player.y = SCREEN_HEIGHT - 2;
    game->player.playerpulando = 0;
    game->player.timerpulo = 0;
    game->obstaculos = NULL;
    game->game_over = 0;
    game->score = 0;
    srand(time(NULL));
    return game;
}

void add_obstaculo(Game *game, int x, int y) {
    Obstaculo *novo = malloc(sizeof(Obstaculo));
    novo->x = x;
    novo->y = y;
    novo->proximo = NULL;
    if (!game->obstaculos) {
        game->obstaculos = novo;
    } else {
        Obstaculo *temp = game->obstaculos;
        while (temp->proximo)
            temp = temp->proximo;
        temp->proximo = novo;
    }
}

void remove_obstaculo(Game *game) {
    if (game->obstaculos) {
        Obstaculo *temp = game->obstaculos;
        game->obstaculos = temp->proximo;
        free(temp);
    }
}

void update_game(Game *game) {
    if (game->player.playerpulando) {
        game->player.timerpulo--;
        if (game->player.timerpulo <= 0) {
            game->player.playerpulando = 0;
            game->player.y = SCREEN_HEIGHT - 2;
        } else {
            game->player.y = SCREEN_HEIGHT - 4;
        }
    }

    Obstaculo *temp = game->obstaculos, *prev = NULL;
    while (temp) {
        temp->x--;
        if (temp->x < 0) {
            if (prev) prev->proximo = temp->proximo;
            else       game->obstaculos = temp->proximo;
            Obstaculo *aRemover = temp;
            temp = temp->proximo;
            free(aRemover);
            game->score++;
            continue;
        }
        prev = temp;
        temp = temp->proximo;
    }

    if (rand() % 20 == 0)
        add_obstaculo(game, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 2);

    temp = game->obstaculos;
    while (temp) {
        if (temp->x == game->player.x && temp->y == game->player.y)
            game->game_over = 1;
        temp = temp->proximo;
    }

    if (kbhit()) {
        int ch = getch();
        if ((ch == ' ' || ch == 'w') && !game->player.playerpulando) {
            game->player.playerpulando = 1;
            game->player.timerpulo = 5;
        }
    }
}

void render_game(Game *game) {
    gotoxy(game->player.x, game->player.y);
    printf("A");
    Obstaculo *temp = game->obstaculos;
    while (temp) {
        gotoxy(temp->x, temp->y);
        printf("#");
        temp = temp->proximo;
    }
    gotoxy(0, 0);
    printf("Score: %d", game->score);
}

void destroy_game(Game *game) {
    Obstaculo *temp = game->obstaculos;
    while (temp) {
        Obstaculo *aRemover = temp;
        temp = temp->proximo;
        free(aRemover);
    }
    free(game);
}

void save_scores(Game *game) {
    FILE *fp = fopen("scores.txt", "a");
    if (fp) {
        fprintf(fp, "%d\n", game->score);
        fclose(fp);
    }
}

void show_start_screen() {
    clear_screen();
    printf("=== JOGO DO CORREDOR ===\n");
    printf("Pressione ESPAÇO para pular\n");
    printf("Pressione qualquer tecla para começar...\n");
    wait_for_key();
}

void show_game_over_screen(Game *game) {
    clear_screen();
    printf("=== FIM DE JOGO ===\n");
    printf("Seu score foi: %d\n", game->score);
    printf("Pressione qualquer tecla para sair...\n");
    wait_for_key();
}
