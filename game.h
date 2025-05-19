#ifndef GAME_H
#define GAME_H

typedef struct {
    int x;
    int y;
    int is_jumping;
    int jump_timer;
} Player;

typedef struct {
    Player player;
    int game_over;
    int ground_y;
} Game;

Game *init_game();
void jump_player(Game *game);
void update_game(Game *game);
void render_game(Game *game);
void save_scores(Game *game);
void destroy_game(Game *game);

#endif
