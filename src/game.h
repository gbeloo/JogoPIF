#ifndef GAME_H
#define GAME_H

#define MAX_OBSTACULOS 10
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24

typedef struct Obstaculo {
    int x, y;
    struct Obstaculo *proximo;
} Obstaculo;

typedef struct Player {
    int x, y;
    int playerpulando;
    int timerpulo;
} Player;

typedef struct Game {
    Player player;
    Obstaculo *obstaculos;
    int game_over;
    int score;
} Game;

Game* init_game();
void update_game(Game *game);
void render_game(Game *game);
void destroy_game(Game *game);
void save_scores(Game *game);
void show_start_screen();
void show_game_over_screen(Game *game);

#endif
