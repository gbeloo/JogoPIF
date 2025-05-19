#include <stdio.h>
#include <stdlib.h>
#include "../cli-lib/cli.h"
#include "game.h"

Game *init_game() {
    Game *game = (Game *) malloc(sizeof(Game));
    if (game == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    game->game_over = 0;
    game->ground_y = 10;
    game->player.x = 5;
    game->player.y = game->ground_y;
    game->player.is_jumping = 0;
    game->player.jump_timer = 0;

    return game;
}

void jump_player(Game *game) {
    if (game->player.is_jumping == 0) {
        game->player.is_jumping = 1;
        game->player.jump_timer = 5;
    }
}

void update_game(Game *game) {
    if (key_pressed() != 0) {
        char key = read_key();

        if (key == 'a' || key == 'A') {
            game->player.x -= 1;
        } else if (key == 'd' || key == 'D') {
            game->player.x += 1;
        } else if (key == ' ') {
            jump_player(game);
        }
    }

    if (game->player.is_jumping == 1) {
        game->player.y -= 1;
        game->player.jump_timer -= 1;

        if (game->player.jump_timer == 0) {
            game->player.is_jumping = 0;
        }
    } else {
        if (game->player.y < game->ground_y) {
            game->player.y += 1;
        }
    }
}

void render_game(Game *game) {
    gotoxy(game->player.x, game->player.y);
    printf("O");
}

void save_scores(Game *game) {
    
}

void destroy_game(Game *game) {
    if (game != NULL) {
        free(game);
    }
}
